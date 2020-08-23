#include "channel.hpp"

void Channel::label(uint16_t code, char *buf) {
  unsigned char c;
  c = (unsigned char)(code & 0xff);

  if(code < 0x100) {
    strcpy_P(buf, (const char *)pgm_read_word(&channels[c]));
  } else if(code < 0x170) {
    strcpy_P(buf, (const char *)pgm_read_word(&channels_2[c]));
  } else {
    strcpy_P(buf, unkn);
  }
}
