#pragma once
#include <stdint.h>

class Frame {
private:
  uint8_t _to;
  uint8_t _from;
  uint8_t _cmd;
  uint8_t _length;
  uint8_t * _data;
  uint16_t _count = 0;
  char _str[1000];

public:
  Frame();
  void set_header(uint8_t to, uint8_t from, uint8_t length, uint8_t cmd);
  void set_data(uint8_t *data);
  char * print();
  uint8_t from();
  uint8_t command();
  uint8_t &operator[](int);
};
