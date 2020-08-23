#include "command.hpp"

void Command::label(uint8_t code, char *buf) {
  strcpy_P(buf, (const char *)pgm_read_word(&commands[code]));
}
