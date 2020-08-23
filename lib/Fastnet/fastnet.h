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
#include <HardwareSerial.h>
#include <LinkedList.h>
#include "channel.hpp"
#include "command.hpp"
#include "node.hpp"
#include "frame.hpp"

#ifndef ENABLE
#define ENABLE 2
#endif

#define IO Serial1

typedef void (* func_t)(uint8_t *);


// Fastnet frame
//       0. destination address
//       1. sender address
//       2. data length (less checksum) (max 249 bytes)
//       3. command
//       4. header checksum (sum of bytes 0 to 4 = 0)
// 5 to nn. data
//  nn + 1. checksum (sum of bytes 5 to nn = 0)

typedef enum { D_NONE = 0x0, D_ONE, D_TWO, D_THREE } divisor;
typedef enum { W_FOUR = 0x0, W_THREE, W_TWO, W_ONE }  width;
typedef enum {
  F_NONE = 0x0, F_NUMBER, F_RES0, F_EQUAL,
  F_RAW_A, F_TIME, F_TEXT, F_MINUTES,
  F_DEGREES, F_RES1, F_RAW_B,
  } format;

// Format options
// NONE: Blank display
// EQUAL: Prefix value with equal sign (segments A and G lit)
// RAW_A: 
// TIME: Value is time, first byte is left of colon, second byte is right
// TEXT: S

class Fastnet {
  uint8_t _len;
  uint8_t _addr;
  uint8_t _seq;
  uint16_t _devices;
  uint8_t _device;
  uint8_t _page;
  uint8_t _buf[256];
  bool    _pause;

  public:
    Fastnet(uint8_t addr);
    void register_device(uint8_t id);
    bool device_exists(uint8_t id);
    uint8_t depth(uint16_t depth);
    uint8_t boat_speed(uint16_t speed);
    uint8_t vmg(uint16_t vmg);
    uint8_t app_wind(int16_t angle, uint16_t speed);
    uint8_t true_wind(int16_t angle, uint16_t speed);
    uint8_t backlight(uint8_t level);
    uint8_t timer(uint16_t seconds);
    uint8_t startup();
    uint8_t who();
    uint8_t new_text();
    uint8_t ask(uint8_t meter);
    uint8_t change_page(uint8_t dir);
    uint8_t config_page(uint16_t channel, uint8_t node, char * label, char * units);
    uint8_t store_page();
    uint8_t raw(const uint8_t * data, uint8_t len);
    uint8_t command(const uint8_t * data, uint8_t len);
    uint8_t checksum(uint8_t * data, uint8_t len);
    void pause();
    void resume();
    void register_callback(const uint8_t command, const func_t &func);
    uint8_t get_device();
    void set_device(uint8_t device);
    uint8_t get_page();
    void set_page(uint8_t page);

  private:
    uint8_t write();
    uint8_t get_formatter(format f, divisor d, width w);
};
