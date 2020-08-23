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

#include "fastnet.h"
#include "actions.h"

extern Fastnet * fastnet;
bool _pause = false;

void start_setup() {
	pause();
	config(0);
}

void end_setup() {
	fastnet->store_page();
	resume();
}

void next_page() {
  fastnet->change_page(0);
}

void previous_page() {
  fastnet->change_page(1);
}

void next_device() {
  fastnet->store_page();
  uint8_t d = fastnet->get_device();

  d++;
  if(d == 0x50) d = 0x40;

  bool f = false;
  for(; d < 0x50; d++) {
    if(fastnet->device_exists(d)) {
      f = true;
      break;
    }
  }

  if(!f) {
    for(d = 0x40; d < 0x50; d++) {
      if(fastnet->device_exists(d)) {
        break;
      }
    }
  }

  fastnet->set_device(d);
  fastnet->change_page(0xFF);
}

void previous_device() {
  fastnet->store_page();
  auto d = fastnet->get_device();

  d--;
  if(d == 0x3F) d = 0x4F;

  for(; d > 0x3F; d--) {
    if(fastnet->device_exists(d)) {
      break;
    }
  }

  fastnet->set_device(d);
  fastnet->change_page(0xFF);
}

bool paused() {
  return _pause;
}

void pause() {
	_pause = true;
}

void resume() {
	_pause = false;
}

void backlight_off() {
	fastnet->backlight(0);
}

void backlight_low() {
	fastnet->backlight(1);
}

void backlight_medium() {
	fastnet->backlight(2);
}

void backlight_high() {
	fastnet->backlight(4);
}

void config(uint16_t code) {
  if(code == 0) {
    fastnet->change_page(0xff);
    return;
  }

  char lbl[32];

  Channel::label(code, lbl);

  auto l = strlen(lbl);

  // capitalize
  for(size_t i = 0; i < l; i++) {
    if(lbl[i] > 0x60 && lbl[i] < 0x7B)
      lbl[i] = lbl[i] & ~0x20;
  }

  // pad with space
  if(l < 10) {
    memset(lbl + l, 0x20, 10 - l);
  }

  fastnet->config_page(code, WIND_CPU, lbl, NULL);
  fastnet->store_page();
}
