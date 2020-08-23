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

String _buf;
bool _repl;
bool _cmd;

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

bool in_repl() {
  return _repl;
}

bool in_cmd() {
  return _cmd;
}

void start_repl() {
  Serial.println(F("Enter the bytes you want to send."));
  Serial.println(F("To send the word OFF, try 0600BEE8E8"));
  Serial.println(F("To return to the menu, enter X"));
  Serial.print("> ");

  _repl = true;
}

void start_cmd() {
  Serial.println(F("Enter the command you want to send."));
  Serial.println(F("The first byte is interpreted as the command, "));
  Serial.println(F("remaining bytes are payload."));
  Serial.println(F("To send a power off command, try C8"));
  Serial.println(F("To send an low boat speed alarm, try E2 01 41"));
  Serial.print("> ");

  _cmd = true;
}

void repl(uint8_t * data, void (* sender)(uint8_t *, int)) {
  _repl = true;

  if(!Serial.available()) return;

  char rx = Serial.read();
  Serial.print(rx);

  if(rx == '\n') {
    if (_buf[0] == 'X' || _buf[0] == 'x') {
      _buf = "";
      _repl = false;
      return;
    }

    int l = to_bytes(data);

    Serial.print("P:");
    for(int i = 0; i < l; i++) {
      Serial.print(' ');
      if(data[i] < 0x10)
        Serial.print('0');
      Serial.print(data[i], HEX);
    }
    Serial.println();

    sender(data, l);

    Serial.print("\n> ");

    _buf = "";
  } else if(rx == 0x08 || rx == 0x7F) {
    _buf.remove(_buf.length() - 1);
  } else if(rx > 0x1F && rx < 0x7F) {
    _buf += rx;
  }
}

void cmd(uint8_t * data, void (* sender)(uint8_t *, int)) {
  _cmd = true;

  if(!Serial.available()) return;

  char rx = Serial.read();
  Serial.print(rx);

  if(rx == '\n') {
    if (_buf[0] == 'X' || _buf[0] == 'x') {
      _buf = "";
      _cmd = false;
      return;
    }

    int l = to_bytes(data);

    Serial.print("P:");
    for(int i = 0; i < l; i++) {
      Serial.print(' ');
      if(data[i] < 0x10)
        Serial.print('0');
      Serial.print(data[i], HEX);
    }
    Serial.println();

    sender(data, l);

    Serial.print("\n> ");

    _buf = "";
  } else if(rx == 0x08 || rx == 0x7F) {
    _buf.remove(_buf.length() - 1);
  } else if(rx > 0x1F && rx < 0x7F) {
    _buf += rx;
  }
}
