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

#include <Arduino.h>
#include "fastnet.h"

Fastnet::Fastnet(uint8_t addr) {
  _addr = addr;
  _seq = 0;
  _pause = false;
  _devices = 0;
  _device = 0x40;
  IO.begin(28800, SERIAL_8O2);
}

void Fastnet::register_device(uint8_t id) {
  if(id >= 0x40 && id <= 0x4f) {
    Serial.print("Registered 20/20 ");
    Serial.println(id - 0x40);
    _devices |= (1 << (id - 0x40));
  }
}

bool Fastnet::device_exists(uint8_t id) {
  return _devices & (1 << (id - 0x40));
}

uint8_t Fastnet::get_device() {
  return _device;
}

void Fastnet::set_device(uint8_t device) {
  _device = device;
}

uint8_t Fastnet::get_page() {
  return _page;
}

void Fastnet::set_page(uint8_t page) {
  _page = page;
}

uint8_t Fastnet::depth(uint16_t depth) {
  uint16_t depth_m = depth / 3.281;
  _buf[0] = BROADCAST;
  _buf[1] = DEPTH_CPU;
  _buf[2] = 0x08;
  _buf[3] = CM_SEND_DATA;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = CH_DEPTH_FT;
  _buf[6] = 0x81; // 2 decimal, 4 digits, number
  _buf[7] = depth >> 8;
  _buf[8] = depth & 0xff;
  _buf[9] = CH_DEPTH_M;
  _buf[10] = 0x81;
  _buf[11] = depth_m >> 8;
  _buf[12] = depth_m & 0xff;
  _buf[13] = checksum(_buf + 5, 8);
  _len = 14;

  return write();
}

uint8_t Fastnet::boat_speed(uint16_t speed) {
  _buf[0] = BROADCAST;
  _buf[1] = DEPTH_CPU;
  _buf[2] = 0x04;
  _buf[3] = CM_SEND_DATA;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = CH_BOAT_SPD_KT;
  _buf[6] = 0x81;
  _buf[7] = speed >> 8;
  _buf[8] = speed & 0xff;
  _buf[9] = checksum(_buf + 5, 4);
  _len = 10;

  return write();
}

uint8_t Fastnet::vmg(uint16_t vmg) {
  _buf[0] = BROADCAST;
  _buf[1] = WIND_CPU;
  _buf[2] = 0x04;
  _buf[3] = CM_SEND_DATA;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = CH_VMG;
  _buf[6] = 0x81;
  _buf[7] = vmg >> 8;
  _buf[8] = vmg & 0xff;
  _buf[9] = checksum(_buf + 5, 4);
  _len = 10;

  return write();
}

uint8_t Fastnet::app_wind(int16_t angle, uint16_t speed) {
  uint8_t waf = 0x71;

  if (angle > 999 || angle < -999) {
    angle /= 10;
    waf = 0x31;
  }
  
  _buf[0] = BROADCAST;
  _buf[1] = WIND_CPU;
  _buf[2] = 0x08;
  _buf[3] = CM_SEND_DATA;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = CH_APP_WS_KT;
  _buf[6] = 0x91;
  _buf[7] = speed >> 8;
  _buf[8] = speed & 0xff;
  _buf[9] = CH_APP_WA;
  _buf[10] = waf;
  _buf[11]= angle >> 8;
  _buf[12] = angle & 0xff;
  _buf[13] = checksum(_buf + 5, 8);
  _len = 14;

  return write();
}

uint8_t Fastnet::true_wind(int16_t angle, uint16_t speed) {
  uint8_t waf = 0x71;

  if (angle > 999 || angle < -999) {
    angle /= 10;
    waf = 0x31;
  }
  
  _buf[0] = BROADCAST;
  _buf[1] = WIND_CPU;
  _buf[2] = 0x08;
  _buf[3] = CM_SEND_DATA;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = CH_TRUE_WS_KT;
  _buf[6] = 0x91;
  _buf[7] = speed >> 8;
  _buf[8] = speed & 0xff;
  _buf[9] = CH_TRUE_WA;
  _buf[10] = waf;
  _buf[11]= angle >> 8;
  _buf[12] = angle & 0xff;
  _buf[13] = checksum(_buf + 5, 8);
  _len = 14;

  return write();
}

uint8_t Fastnet::timer(uint16_t seconds) {
  uint8_t m = seconds / 60;
  uint8_t s = seconds % 60;

  _buf[0] = BROADCAST;
  _buf[1] = WIND_CPU;
  _buf[2] = 0x08;
  _buf[3] = CM_SEND_DATA;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = CH_TIMER;
  _buf[6] = 0x00;
  _buf[7] = m;
  _buf[8] = s;
  _buf[9] = checksum(_buf + 5, 8);
  _len = 10;

  return write();
}

// Write data to channel Linear 1 without any formatting
// Learn how the display formatting bytes work
uint8_t Fastnet::raw(const uint8_t * data, uint8_t len) {
  _buf[0] = BROADCAST;
  _buf[1] = WIND_CPU;
  _buf[2] = len;
  _buf[3] = CM_SEND_DATA;
  _buf[4] = checksum(_buf, 4);
  _len = 5;

  if(len) {
    _buf[2] = len + 1;
    _buf[4] = checksum(_buf, 4);
    _buf[5] = CH_LINEAR_1;
    memcpy(_buf + 6, data, len);
    _buf[6 + len] = checksum(_buf + 5, len + 1);
    _len = len + 7;
  }

  return write();
}

uint8_t Fastnet::backlight(uint8_t level) {
  _buf[0] = BROADCAST;
  _buf[1] = _addr;
  _buf[2] = 0x02;
  _buf[3] = CM_SET_BACKLIGHT;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = level;
  _buf[6] = 0x20;
  _buf[7] = checksum(_buf + 5, 2);
  _len = 8;

  return write();
}

uint8_t Fastnet::startup() {
  _buf[0] = BROADCAST;
  _buf[1] = _addr;
  _buf[2] = 0x00;
  _buf[3] = CM_STARTUP;
  _buf[4] = checksum(_buf, 4);
  _len = 5;

  return write();
}

uint8_t Fastnet::who() {
  _buf[0] = BROADCAST;
  _buf[1] = _addr;
  _buf[2] = 0x00;
  _buf[3] = CM_WHO;
  _buf[4] = checksum(_buf, 4);
  _len = 5;

  return write();
}

uint8_t Fastnet::new_text() {
  _buf[0] = BROADCAST;
  _buf[1] = _addr;
  _buf[2] = 0x00;
  _buf[3] = CM_NEW_TEXT;
  _buf[4] = checksum(_buf, 4);
  _len = 5;

  return write();
}

uint8_t Fastnet::ask(uint8_t meter) {
  _buf[0] = BROADCAST;
  _buf[1] = _addr;
  _buf[2] = 0x02;
  _buf[3] = CM_REQ_CONNECTED;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = _seq;
  _buf[6] = meter;
  _buf[7] = checksum(_buf + 5, 2);
  _len = 8;

  return write();
}

uint8_t Fastnet::change_page(uint8_t dir) {
  _buf[0] = _device;
  _buf[1] = _addr;
  _buf[2] = 0x02;
  _buf[3] = CM_CHANGE_PAGE;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = _seq;
  _buf[6] = dir;
  _buf[7] = checksum(_buf + 5, 2);
  _len = 8;

  return write();
}

uint8_t Fastnet::config_page(uint16_t channel, uint8_t node, char * label, char * units) {
  _buf[0] = _device;
  _buf[1] = _addr;
  _buf[2] = 0x0E;
  if (channel > 0xff) _buf[2]++;
  _buf[3] = CM_CURRENT_PAGE;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = _seq;
  _buf[6] = _page;

  int i = 7;

  if(channel > 0xff) {
    _buf[i] = channel >> 8;
    _buf[i+1] = channel & 0xff;
    _buf[i+2] = node;
    _len = 21;
    i += 3;
  } else {
    _buf[i] = channel;
    _buf[i+1] = node;
    _len = 20;
    i += 2;
  }

  if(units) {
    memcpy(_buf + i, label, 8);
    memcpy(_buf + i + 8, units, 2);
  } else {
    memcpy(_buf + i, label, 10);
  }

  i += 10;

  _buf[i] = checksum(_buf + 5, i - 5);

  return write();
}

uint8_t Fastnet::store_page() {
  _buf[0] = _device;
  _buf[1] = _addr;
  _buf[2] = 0x01;
  _buf[3] = CM_SELECT_PAGE;
  _buf[4] = checksum(_buf, 4);
  _buf[5] = _seq;
  _buf[6] = checksum(_buf + 5, 1);
  _len = 7;

  auto r = write();
  _pause = true;
  delay(100);
  _pause = false;

  return r;
}

uint8_t Fastnet::checksum(uint8_t *data, uint8_t len) {
  uint8_t sum = 0;
  for(uint8_t i = 0; i < len; i++)
    sum += data[i];

  return ~sum + 1;
}

void Fastnet::pause() {
  _pause = true;
}

void Fastnet::resume() {
  _pause = false;
}

uint8_t Fastnet::write() {
  digitalWrite(ENABLE, HIGH);
  Serial.print("TX: ");
  for(int i = 0; i < _len; i++) {
    Serial.print(_buf[i], HEX);
    Serial.print(' ');
  }
  Serial.println();

  if(!_pause) {
    IO.write(_buf, _len);
    _seq++;
    return _len;
  }

  return _len;
}
