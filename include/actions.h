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

#include "stdint.h"

void start_setup();
void end_setup();
void next_page();
void previous_page();
void next_device();
void previous_device();
bool paused();
void pause();
void resume();
void backlight_low();
void backlight_medium();
void backlight_high();
void backlight_off();
void config(uint16_t);
