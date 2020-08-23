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
