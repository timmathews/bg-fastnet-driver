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
#include "SerialMenu.hpp"

const char PROGMEM item0[] = "Setup";
const char PROGMEM item1[] = "Redisplay";
const char PROGMEM item2[] = "Back";
const char PROGMEM item3[] = "Backlight Off";
const char PROGMEM item4[] = "Backlight Low";
const char PROGMEM item5[] = "Backlight Med";
const char PROGMEM item6[] = "Backlight High";
const char PROGMEM item7[] = "Pause";
const char PROGMEM item8[] = "Resume";
const char PROGMEM item9[] = "Send Raw Data";

const char PROGMEM item10[] = "Previous Device";
const char PROGMEM item11[] = "Next Device";
const char PROGMEM item12[] = "Previous Page";
const char PROGMEM item13[] = "Next Page";
const char PROGMEM item14[] = "Select Channel";

const char PROGMEM item20[] = "Speed";
const char PROGMEM item21[] = "Log";
const char PROGMEM item22[] = "Depth";
const char PROGMEM item23[] = "Navigate";
const char PROGMEM item24[] = "Wind";
const char PROGMEM item25[] = "Perform";
const char PROGMEM item26[] = "Waypoint";
const char PROGMEM item27[] = "Motor";
const char PROGMEM item28[] = "Temp";
const char PROGMEM item29[] = "Time";
const char PROGMEM item2A[] = "Misc";
const char PROGMEM item2B[] = "Loadcells";

const char PROGMEM item200[] = "Boat Speed";
const char PROGMEM item201[] = "Avg Speed";
const char PROGMEM item202[] = "VMG";

const char PROGMEM item210[] = "Stored log";
const char PROGMEM item211[] = "Trip log";

const char PROGMEM item220[] = "Depth M";
const char PROGMEM item221[] = "Depth Ft";
const char PROGMEM item222[] = "Depth Fm";

const char PROGMEM item230[] = "Heading";
const char PROGMEM item231[] = "Off Course";
const char PROGMEM item232[] = "D/R Course";
const char PROGMEM item233[] = "D/R Distance";
const char PROGMEM item234[] = "Course";
const char PROGMEM item235[] = "Leeway";
const char PROGMEM item236[] = "Tide Set";
const char PROGMEM item237[] = "Tide Drift";

const char PROGMEM item240[] = "Apparent W/S kts";
const char PROGMEM item241[] = "True W/S kts";
const char PROGMEM item242[] = "Apparent W/A";
const char PROGMEM item243[] = "True W/A";
const char PROGMEM item244[] = "True Wind Dir";
const char PROGMEM item245[] = "Lift / Head";
const char PROGMEM item246[] = "Next Leg AWA";
const char PROGMEM item247[] = "Next Leg AWS";
const char PROGMEM item248[] = "Upwash";
const char PROGMEM item249[] = "Apparent W/S m/s";
const char PROGMEM item24A[] = "True W/S m/s";

const char PROGMEM item250[] = "Tacking";
const char PROGMEM item251[] = "Reaching";
const char PROGMEM item252[] = "Optimum W/A";
const char PROGMEM item253[] = "Dist to Layline";
const char PROGMEM item254[] = "Heel";
const char PROGMEM item255[] = "Target Speed";
const char PROGMEM item256[] = "Heading on Opposite Tack";
const char PROGMEM item257[] = "Fore/Aft Trim";
const char PROGMEM item258[] = "Mast Angle";
const char PROGMEM item259[] = "Wind Angle to Mast";

const char PROGMEM item260[] = "Bearing Wpt to Wpt T";
const char PROGMEM item261[] = "Bearing Wpt to Wpt M";
const char PROGMEM item262[] = "Bearing to Wpt Rhumb T";
const char PROGMEM item263[] = "Bearing to Wpt Rhumb M";
const char PROGMEM item264[] = "Bearing to Wpt G/C T";
const char PROGMEM item265[] = "Bearing to Wpt G/C M";
const char PROGMEM item266[] = "Distance to Wpt Rhumb";
const char PROGMEM item267[] = "Distance to Wpt G/C";
const char PROGMEM item268[] = "Course Over Ground T";
const char PROGMEM item269[] = "Course Over Ground M";
const char PROGMEM item26A[] = "Speed Over Ground";
const char PROGMEM item26B[] = "VMG to Wpt";
const char PROGMEM item26C[] = "Time to Wpt";
const char PROGMEM item26D[] = "Cross Track Error";
const char PROGMEM item26E[] = "Latitude";
const char PROGMEM item26F[] = "Longitude";

const char PROGMEM item270[] = "Battery Volts";

const char PROGMEM item280[] = "Sea Temp F";
const char PROGMEM item281[] = "Sea Temp C";
const char PROGMEM item282[] = "Air Temp F";
const char PROGMEM item283[] = "Air Temp C";

const char PROGMEM item290[] = "Timer";

const char PROGMEM item2A0[] = "Rudder Angle";
const char PROGMEM item2A1[] = "Linear 1";
const char PROGMEM item2A2[] = "Linear 2";
const char PROGMEM item2A3[] = "Linear 3";
const char PROGMEM item2A4[] = "Linear 4";
const char PROGMEM item2A5[] = "Barometer";
const char PROGMEM item2A6[] = "Baro. Trend";

const char PROGMEM item2B0[] = "Forestay";
const char PROGMEM item2B1[] = "Backstay";
const char PROGMEM item2B2[] = "Boom Vang";
const char PROGMEM item2B3[] = "Inner Forestay";
const char PROGMEM item2B4[] = "Inner Forestay Halyard";
const char PROGMEM item2B5[] = "Jib Furler";
const char PROGMEM item2B6[] = "Jib Halyard";
const char PROGMEM item2B7[] = "Outhaul";
const char PROGMEM item2B8[] = "Cunningham";
const char PROGMEM item2B9[] = "Code Zero";
const char PROGMEM item2BA[] = "Bobstay";
const char PROGMEM item2BB[] = "Mainsheet";
const char PROGMEM item2BC[] = "Port Runner";
const char PROGMEM item2BD[] = "Starboard Runner";
const char PROGMEM item2BE[] = "Port Deflector";
const char PROGMEM item2BF[] = "Starboard Deflector";

extern SerialMenu &menu;
void load_menu();
