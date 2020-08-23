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
#include "common.hpp"

#define DEPTH_CPU   0x01
#define WIND_CPU    0x05
#define PERF_CPU    0x09
#define EXP_01      0x0D
#define EXP_02      0x0E
#define HALCYON_CPU 0x0F

#define H2000_GYRO  0x10
#define ACP_GYRO    0x12

#define FFD         0x20 // thru 0x2F
#define HALCYON_FFD 0x30 // thru 0x3F
#define D2020       0x40 // thru 0x4F
#define PILOT       0x50 // thru 0x5F
#define NMEA        0x60 // thru 0x6E
#define WIRELESS    0x6F
#define LOADCELL    0x70 // thru 0x7F
#define TANK_LEVEL  0x80

#define ALL_2020  0xFA
#define ALL_H_FFD 0xFB
#define ALL_P_FFD 0xFC
#define ALL_CPU   0xFD
#define ALL_FFD   0xFE
#define BROADCAST 0xFF

const char PROGMEM node_depth[] = "Depth CPU";
const char PROGMEM node_wind[]  = "Wind CPU";
const char PROGMEM node_perf[]  = "Performance CPU";
const char PROGMEM node_exp_1[] = "Expansion 1";
const char PROGMEM node_exp_2[] = "Expansion 2";
const char PROGMEM node_halcyon[] = "Halcyon CPU";
const char PROGMEM node_h2k_gyro[] = "H2000 Gyro";
const char PROGMEM node_acp_gyro[] = "ACP Gyro";
const char PROGMEM node_ffd[] = "FFD";
const char PROGMEM node_halcyon_ffd[] = "Halcyon FFD";
const char PROGMEM node_2020[] = "20/20 Display";
const char PROGMEM node_pilot[] = "Pilot FFD";
const char PROGMEM node_nmea[] = "NMEA FFD";
const char PROGMEM node_wireless[] = "Wireless Interface";
const char PROGMEM node_loadcell[] = "Loadcell Amplifier";
const char PROGMEM node_tank[] = "Tank Level Sensor";

const char PROGMEM group_2020[] = "All 20/20 Displays";
const char PROGMEM group_h_ffd[] = "All Halcyon FFDs";
const char PROGMEM group_p_ffd[] = "All Pilot FFDs";
const char PROGMEM group_cpu[] = "All System CPUs";
const char PROGMEM group_ffd[] = "All FFDs";
const char PROGMEM broadcast[] = "Broadcast";

class Node {
private:
  Node();

public:
  static void name(uint8_t a, char *buf);
};
