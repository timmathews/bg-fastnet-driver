/*
 * B&G Fastnet Interface
 * Copyright (C) 2020 Tim Mathews <tim@signalk.org>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "repl.h"

enum mode_t { DATA, CMD, NONE };

String _buf;
mode_t _mode = NONE;
uint8_t h = 0;
uint8_t m = 0;
uint8_t s = 0;
uint8_t x = 0x80;
bool repeat;

int send_time(uint8_t * buf) {
  buf[0] = 0x05;
  buf[1] = x;
  buf[2] = 0;//x & 0xFF;
  buf[3] = h;
  buf[4] = m;
  buf[5] = s;

  x += 0x01;
  s++;
  m++;

  if(s == 60) {
    s = 0;
  }

  if(m == 60) {
    m = 0;
    h++;
  }

  if(h == 100)
    h = 0;

  return 6;
}

char ctoh(char c) {
  if(c >= '0' && c <= '9') return c - '0';
  if(c >= 'A' && c <= 'F') return c - 'A' + 10;
  if(c >= 'a' && c <= 'f') return c - 'a' + 10;
  return 0;
}

int to_bytes(uint8_t * buf) {
  int i = 0;

  for(;;) {
    char h = _buf[2*i];
    if(h == 0) break;
    char l = _buf[2*i+1];
    buf[i] = (ctoh(h)<<4) + ctoh(l);
    i++;
  }

  return i;
}

void print_payload(uint8_t * data, int l) {
    Serial.print("P:");

    for(int i = 0; i < l; i++) {
      Serial.print(' ');
      if(data[i] < 0x10)
        Serial.print('0');
      Serial.print(data[i], HEX);
    }

    Serial.println();
}

bool in_data() {
  return _mode == DATA;
}

bool in_cmd() {
  return _mode == CMD;
}

void start_data() {
  Serial.println(F("Enter the bytes you want to send."));
  Serial.println(F("To send the word OFF, try 0600BEE8E8"));
  Serial.println(F("To return to the menu, enter X"));
  Serial.print("> ");

  _mode = DATA;
}

void start_cmd() {
  Serial.println(F("Enter the command you want to send."));
  Serial.println(F("The first byte is interpreted as the command, "));
  Serial.println(F("remaining bytes are payload."));
  Serial.println(F("To send a power off command, try C8"));
  Serial.println(F("To send an low boat speed alarm, try E2 01 41"));
  Serial.print("> ");

  _mode = CMD;
}

void repl(uint8_t * data, void (* sender)(uint8_t *, int), void(* on_exit)()) {
  if(!Serial.available()) return;

  char rx = Serial.read();
  Serial.print(rx);

  if(rx == '\n') {
    if (_buf[0] == 'X' || _buf[0] == 'x') {
      _buf = "";
      _mode = NONE;
      on_exit();
      return;
    }

    int l = to_bytes(data);
    print_payload(data, l);
    sender(data, l);
    Serial.print("\n> ");
    _buf = "";
  } else if(rx == 0x08 || rx == 0x7F) {
    _buf.remove(_buf.length() - 1);
  } else if(rx > 0x1F && rx < 0x7F) {
    _buf += rx;
  }
}
