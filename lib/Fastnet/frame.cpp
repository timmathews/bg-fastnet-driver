#include "frame.hpp"
#include "node.hpp"
#include "command.hpp"
#include "stdio.h"
#include <HardwareSerial.h>

Frame::Frame() {}

void Frame::set_header(uint8_t to, uint8_t from, uint8_t length, uint8_t cmd) {
  _to = to;
  _from = from;
  _cmd = cmd;
  _length = length;
  _count++;
}

void Frame::set_data(uint8_t *p) {
  _data = p;
}

char * Frame::print() {
  char * s = _str;
  int l;
  s += snprintf(s, 1000, "Frame:   %d\nTo:      %02X ", _count, _to);

  Node::name(_to, s);
  l = strlen(s);
  s += l;

  s += snprintf(s, 1000 - l, "\nFrom:    %02X ", _from);

  Node::name(_from, s);
  l = strlen(s);
  s += l;

  s += snprintf(s, 1000 - l, "\nLength:  %02x\nCommand: %02X ", _length, _cmd);

  Command::label(_cmd, s);
  l = strlen(s);
  s += l;

  if(_length) {
    s += snprintf(s, 1000 - l, "\nData:   ");
    l = strlen(s);

    for(int i = 0; i < _length; i++) {
      s += snprintf(s, 1000 - l, " %02X", _data[i]);
      l += 3;
    }
  }

  s += snprintf(s, 1000 - l, "\n\n");

  return _str;
}

uint8_t Frame::from() {
  return _from;
}

uint8_t Frame::command() {
  return _cmd;
}

uint8_t & Frame::operator[](int i) {
  return _data[i];
}
