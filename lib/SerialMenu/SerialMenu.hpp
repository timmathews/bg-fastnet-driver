//////////////////
// Design overview
//////////////////
// The code is pretty easy to follow. However here are some pointers.
// A menu is defined as an array of SerialMenuEntry elements. Each entry
// tracks a pointer to the callback to run when the menu is selected, a pointer
// to the string to display (the pointer can be a PROGMEM pointer), and a key
// which is the keypress that will trigger the selection of this menu entry.
// The keys are converted to lowercase by OR-ing 0x20. Since the bit 0x20 is
// not used, it is used as a flag to tell if the string is stored in FLASH via
// PROGMEM, or if it is stored in SRAM like regular data.
//
// The SerialMenu class is a singleton class. Only one instance can exist.
// To do so we provide the get() method, which if needed allocates that one
// singleton instance. To prevent other instances to exist, the constructor is
// kept private. Furthermore I declared all the class variables static.
//
// The usage pattern is to copy the pointer to the array. We must pass the size
// too so a macro is provided for that. One those are in SerialMenu, the show()
// command can scan the array to print the menu, and run() can scan the keys to
// detect if an input is a valid menu entry, and if so it calls the callback
// function defined in the array.
// This implementation allows the use of lambda functions in the array. This
// makes for menues that are very concise, where all the data and code for a
// menu entry is declared in one source line. Other solutions will tend to have
// a clutter to support menus and their actions.
// I think I am being clever doing this! :)
//
#pragma once
#include <avr/pgmspace.h>
#include <HardwareSerial.h>

///////////////////////////////////////////////////////////////////////////////
// Define a menu entry as:
// - a menu message to display
// - a boolean to specify if the message is in SRAM or PROGMEM Flash memory
// - a menu key to select
// - a callback function to perform the menu action
///////////////////////////////////////////////////////////////////////////////
class SerialMenuEntry {
  private:
    // Message to display via getMenu()
    // The pointer can be in SRAM or in FLASH (requires PROGMEM to access)
    const char * message;
    // Keyboard character entry to select this menu entry, overloaded:
    // We set bit 0x20 to 0 for normal message, to 1 for a PROGMEM message
    const char key;
    
  public:
    // Callback function that performs this menu's action
    void (*actionCallback)();

    // Constructor used to init the array of menu entries
    SerialMenuEntry(const char * m, bool isprogMem, char k, void (*c)()) :
    message(m), key(((isprogMem) ? (k|0x20) : (k&(~0x20)))), actionCallback(c)
    {}
  
    // Get the menu message to display
    inline const char * getMenu() const
    {
      return message;
    }

    inline bool isProgMem() const
    {
      return key & 0x20;
    }

    inline const char getKey() const
    {
      return key & ~0x20;
    }

    // Check if the user input k matches this menu entry
    // Characters are converted to lowercase ASCII.
    // @note this impacts also symbols, not numbers, so test before using those
    inline bool isChosen(const char k) const
    {
      return (k|0x20) == (key|0x20);
    }
};

///////////////////////////////////////////////////////////////////////////////
// Macro to get the number of menu entries in a menu array.
///////////////////////////////////////////////////////////////////////////////
#define GET_MENU_SIZE(menu) sizeof(menu)/sizeof(SerialMenuEntry)

///////////////////////////////////////////////////////////////////////////////
// The menu is a singleton class in which you load an array of menu entries.
//
///////////
// Example:
///////////
// loop()
// {
//    SerialMenu& menu = SerialMenu::get();
// }
//
// @todo Instead of a singleton we could avoid having any instance and
// convert methods to static methods using static data. It saves a pointer
///////////////////////////////////////////////////////////////////////////////
class SerialMenu
{
  private:
    // If PROGMEM is used, copy using this SRAM buffer size.
    static constexpr uint8_t PROGMEM_BUF_SIZE = 8;

    // This class implements a singleton desgin pattern with one
    // static instance
    static SerialMenu * singleton;

    // Points to the array of menu entries for the current menu
    static const SerialMenuEntry * menu;

    // Count how long we've been waiting for the user to input data
    static uint16_t waiting;

    // number of entries in the current menu
    static uint8_t size;

    // Private constructor for singleton design.
    // Initializes with an empty menu, prepares serial console and staus LED.
    SerialMenu() {}

  public:
    // Get a pointer to the one singleton instance of this class
    static SerialMenu & get()
    {
      if (singleton == nullptr)
      {
        singleton = new SerialMenu;
      }

      return *singleton;
    }

    // Get a pointer to the one singleton instance of this class and point it
    // to the current menu
    static const SerialMenu & get(const SerialMenuEntry* array, uint8_t arraySize)
    {
      (void) SerialMenu::get();
      singleton->load(array, arraySize);
      return *singleton;
    }
    
    // Install the current menu to display
    inline void load(const SerialMenuEntry* array, uint8_t arraySize)
    {
      menu = array;
      size = arraySize;
    }

    // Display the current menu on the Serial console
    void show() const
    {
      Serial.print("\n");
      for (uint8_t i = 0; i < size; ++i)
      {
        Serial.print(menu[i].getKey());
        Serial.print(". ");
        if (menu[i].isProgMem())
        {
          // String in PROGMEM Flash, move it via a SRAM buffer to print it
          char buffer[PROGMEM_BUF_SIZE];
          const char * progMemPt = menu[i].getMenu();
          uint8_t len = strlcpy_P(buffer, progMemPt, PROGMEM_BUF_SIZE);
          Serial.print(buffer);
          while (len >= PROGMEM_BUF_SIZE)
          {
            len -= PROGMEM_BUF_SIZE - 1;
            progMemPt += PROGMEM_BUF_SIZE - 1;
            // @todo replace strlcpy_P() and buffer with moving a uint32?
            len = strlcpy_P(buffer, progMemPt, PROGMEM_BUF_SIZE);
            Serial.print(buffer);
          }
          Serial.println();
        }
        else
        {
          // String in data SRAM, print directly
          Serial.println(menu[i].getMenu());
        }
      }
    }

    ///////////////////////////////////////////////////////////////////////////
    // run the menu. If the user presses a key, it will be parsed, and trigger
    // running the matching menu entry callback action. If not print an error.
    // Returns false if there was no menu input, true if there was
    bool run(const uint16_t loopDelayMs)
    {
      const bool userInputAvailable = Serial.available();

      // Process the input
      if (!userInputAvailable)
      {
        return false;
      }
      else
      {
        // Read one character from the Serial console as a menu choice.
        char menuChoice = Serial.read();
        
        // Menu choice must be in range A-Z (case insensitive)
        if ((menuChoice & ~0x20) < 0x41 || (menuChoice & ~0x20) > 0x5a)
        {
          return false;
        }
       
        uint8_t i;
        for (i = 0; i < size; ++i)
        {
          if (menu[i].isChosen(menuChoice))
          {
            menu[i].actionCallback();
            break;
          }
        }
        if (i == size)
        {
          Serial.print(menuChoice);
          Serial.println(": Invalid menu choice.");
        }
        return true;
      }
    }
};
