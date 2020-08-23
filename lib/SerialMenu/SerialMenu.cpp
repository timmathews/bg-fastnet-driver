///////////////////////////////////////////////////////////////////////////////
// Serial port Menus
// SerialMenu - Copyright (c) 2019 Dan Truong
// See SerialMenu.hpp for details
///////////////////////////////////////////////////////////////////////////////
#include "SerialMenu.hpp"

SerialMenu* SerialMenu::singleton = nullptr;
const SerialMenuEntry* SerialMenu::menu = nullptr;
uint16_t SerialMenu::waiting = uint16_t(0);
uint8_t SerialMenu::size = uint8_t(0);
