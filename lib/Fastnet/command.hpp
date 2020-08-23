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

#define CM_ARP_REQ          0x00
#define CM_SEND_DATA        0x01
#define CM_NEW_TEXT         0x02
#define CM_NMEA_DATA        0x03
#define CM_HELLO            0x0A
#define CM_KEEP_ALIVE       0x0C
#define CM_SECTOR_ALARM     0x20
#define CM_LOW_ALARM_OFF    0x21
#define CM_HIGH_ALARM_OFF   0x22
#define CM_REQUEST_DATA     0x68
#define CM_REQUEST_DATA_2   0x69
#define CM_DATA_REPLY       0x6A
#define CM_POWER_OFF        0xC8
#define CM_SET_BACKLIGHT    0xC9
#define CM_TIMER_START      0xCA
#define CM_TIMER_PAUSE      0xCB
#define CM_TIMER_RUN        0xCC
#define CM_REQ_DAMPING      0xCD
#define CM_GET_SET_DAMPING  0xCE
#define CM_REQ_MAN_CAL      0xCF
#define CM_REACH_CORRECT    0xD0
#define CM_REQ_CAL_2        0xD1
#define CM_CAL_1            0xD3
#define CM_CAL_2            0xD4
#define CM_CAL_3            0xD5
#define CM_CAL_4            0xD6
#define CM_TIMER_FREEZE     0xDC
#define CM_LOW_ALARM_OFF_2  0xDE
#define CM_LOW_ALARM_ON     0xE2
#define CM_ALARM_OFF        0xE6
#define CM_GET_SET_CAL_VAL  0xE9
#define CM_START_AUTO_CAL   0xEA
#define CM_STOP_AUTO_CAL    0xEB
#define CM_END_AUTO_CAL     0xEC
#define CM_CAL              0xED
#define CM_REQ_CAL          0xEE
#define CM_REQ_CONNECTED    0xEF
#define CM_SET_DISPLAY      0xF0
#define CM_MAX_VALUE        0xF1
#define CM_GET_SET_MAX_VAL  0xF2
#define CM_CHANGE_PAGE      0xF6
#define CM_CURRENT_PAGE     0xF7
#define CM_SELECT_PAGE      0xF8
#define CM_ACK_CHAN_ASSIGN  0xFA
#define CM_WHO              0xFB
#define CM_CHAN_ASSIGN      0xFC
#define CM_ACK_SELECT_PAGE  0xFD
#define CM_SYSTEM_RESET     0xFE
#define CM_STARTUP          0xFF

const char PROGMEM cm00[] = "ARP request";
const char PROGMEM cm01[] = "Broadcast data";
const char PROGMEM cm02[] = "Function text";
const char PROGMEM cm03[] = "NMEA data";
const char PROGMEM cm0A[] = "Hello";
const char PROGMEM cm0C[] = "Keepalive";
const char PROGMEM cm20[] = "Sector alarm";
const char PROGMEM cm21[] = "Low alarm off";
const char PROGMEM cm22[] = "High alarm off";
const char PROGMEM cm68[] = "Request data";
const char PROGMEM cm69[] = "Request data";
const char PROGMEM cm6A[] = "Data reply";
const char PROGMEM cmC8[] = "Power off";
const char PROGMEM cmC9[] = "Backlight level";
const char PROGMEM cmCA[] = "Timer start/reset";
const char PROGMEM cmCB[] = "Timer pause/run";
const char PROGMEM cmCC[] = "Timer run";
const char PROGMEM cmCD[] = "Request damping";
const char PROGMEM cmCE[] = "Get/set damping";
const char PROGMEM cmCF[] = "Manual cal";
const char PROGMEM cmD0[] = "Reaching correction";
const char PROGMEM cmD1[] = "Request cal 2";
const char PROGMEM cmD3[] = "Cal 1";
const char PROGMEM cmD4[] = "Cal 2";
const char PROGMEM cmD5[] = "Cal 3";
const char PROGMEM cmD6[] = "Cal 4";
const char PROGMEM cmDC[] = "Timer pause";
const char PROGMEM cmDE[] = "Alarm low off";
const char PROGMEM cmE2[] = "Alarm low on";
const char PROGMEM cmE6[] = "Alarm off";
const char PROGMEM cmE9[] = "Get/set cal value";
const char PROGMEM cmEA[] = "Start boat speed cal run";
const char PROGMEM cmEB[] = "Stop boat speed cal run";
const char PROGMEM cmEC[] = "End boat speed cal run";
const char PROGMEM cmED[] = "Cal";
const char PROGMEM cmEE[] = "Request cal value";
const char PROGMEM cmEF[] = "Request connected meter";
const char PROGMEM cmF0[] = "Set meter display";
const char PROGMEM cmF1[] = "Request max value";
const char PROGMEM cmF2[] = "Get/set max value";
const char PROGMEM cmF6[] = "Change page";
const char PROGMEM cmF7[] = "Current page";
const char PROGMEM cmF8[] = "Select page";
const char PROGMEM cmFA[] = "ACK";
const char PROGMEM cmFB[] = "Request";
const char PROGMEM cmFC[] = "Assign channel";
const char PROGMEM cmFD[] = "ACK Assign channel";
const char PROGMEM cmFE[] = "System reset";
const char PROGMEM cmFF[] = "Hello";

const char *const PROGMEM commands[] = {
  cm00, cm01, cm02, cm03, unkn, unkn, unkn, unkn, unkn, unkn, cm0A, unkn, cm0C, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  cm20, cm21, cm22, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, cm68, cm69, cm6A, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, cmC8, cmC9, cmCA, cmCB, cmCC, cmCD, cmCE, cmCF,
  cmD0, cmD1, unkn, cmD3, cmD4, cmD5, cmD6, unkn, unkn, unkn, unkn, unkn, cmDC, unkn, cmDE, unkn,
  unkn, unkn, cmE2, unkn, unkn, unkn, cmE6, unkn, unkn, cmE9, cmEA, cmEB, cmEC, cmED, cmEE, cmEF,
  cmF0, cmF1, cmF2, unkn, unkn, unkn, cmF6, cmF7, cmF8, unkn, cmFA, cmFB, cmFC, cmFD, cmFE, cmFF,
};

class Command {
private:
  Command();

public:
  static void label(uint8_t code, char *buf);
};
