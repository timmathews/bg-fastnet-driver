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

#include "stdint.h"
#include "menu.h"
#include "fastnet.h"
#include "actions.h"
#include "repl.h"

extern Fastnet * fastnet;
extern const SerialMenuEntry menu0[];
extern const SerialMenuEntry menu1[];
extern const SerialMenuEntry menu2[];
extern const SerialMenuEntry menu20[];
extern const SerialMenuEntry menu21[];
extern const SerialMenuEntry menu22[];
extern const SerialMenuEntry menu23[];
extern const SerialMenuEntry menu24[];
extern const SerialMenuEntry menu25[];
extern const SerialMenuEntry menu26[];
extern const SerialMenuEntry menu27[];
extern const SerialMenuEntry menu28[];
extern const SerialMenuEntry menu29[];
extern const SerialMenuEntry menu2A[];
extern const SerialMenuEntry menu2B[];
extern const uint8_t menu0Size;
extern const uint8_t menu1Size;
extern const uint8_t menu2Size;
extern const uint8_t menu20Size;
extern const uint8_t menu21Size;
extern const uint8_t menu22Size;
extern const uint8_t menu23Size;
extern const uint8_t menu24Size;
extern const uint8_t menu25Size;
extern const uint8_t menu26Size;
extern const uint8_t menu27Size;
extern const uint8_t menu28Size;
extern const uint8_t menu29Size;
extern const uint8_t menu2ASize;
extern const uint8_t menu2BSize;

const SerialMenuEntry menu0[] = {
  { item0, true, 'S', [](){ setup(); menu.load(menu1, menu1Size); menu.show(); }},
  { item3, true, 'O', backlight_off },
  { item4, true, 'L', backlight_low },
  { item5, true, 'M', backlight_medium },
  { item6, true, 'H', backlight_high },
  { item7, true, 'P', pause },
  { item8, true, 'U', resume },
  { item9, true, 'D', start_data },
  { itemA, true, 'C', start_cmd },
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu0Size = GET_MENU_SIZE(menu0);

const SerialMenuEntry menu1[] = {
  { item10, true, 'P', previous_device },
  { item11, true, 'N', next_device },
  { item12, true, 'D', previous_page },
  { item13, true, 'U', next_page },
  { item14, true, 'S', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item2, true, 'B', []() { menu.load(menu0, menu0Size); menu.show(); end_setup(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu1Size = GET_MENU_SIZE(menu1);

const SerialMenuEntry menu2[] = {
  { item20, true, 'S', []() { menu.load(menu20, menu20Size); menu.show(); }},
  { item21, true, 'L', []() { menu.load(menu21, menu21Size); menu.show(); }},
  { item22, true, 'D', []() { menu.load(menu22, menu22Size); menu.show(); }},
  { item23, true, 'N', []() { menu.load(menu23, menu23Size); menu.show(); }},
  { item24, true, 'W', []() { menu.load(menu24, menu24Size); menu.show(); }},
  { item25, true, 'P', []() { menu.load(menu25, menu25Size); menu.show(); }},
  { item26, true, 'A', []() { menu.load(menu26, menu26Size); menu.show(); }},
  { item27, true, 'M', []() { menu.load(menu27, menu27Size); menu.show(); }},
  { item28, true, 'T', []() { menu.load(menu28, menu28Size); menu.show(); }},
  { item29, true, 'I', []() { menu.load(menu29, menu29Size); menu.show(); }},
  { item2A, true, 'C', []() { menu.load(menu2A, menu2ASize); menu.show(); }},
  { item2B, true, 'O', []() { menu.load(menu2B, menu2BSize); menu.show(); }},
  { item2, true, 'B', []() { menu.load(menu1, menu1Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu2Size = GET_MENU_SIZE(menu2);

const SerialMenuEntry menu20[] = {
  { item200, true, 'S', []() { config(CH_BOAT_SPD_KT); }},
  { item201, true, 'A', []() { config(CH_AVG_SPD); }},
  { item202, true, 'V', []() { config(CH_VMG); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu20Size = GET_MENU_SIZE(menu20);

const SerialMenuEntry menu21[] = {
  { item210, true, 'S', []() { config(CH_STD_LOG); }},
  { item211, true, 'T', []() { config(CH_TRIP_LOG); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu21Size = GET_MENU_SIZE(menu21);

const SerialMenuEntry menu22[] = {
  { item220, true, 'M', []() { config(CH_DEPTH_M); }},
  { item221, true, 'T', []() { config(CH_DEPTH_FT); }},
  { item222, true, 'F', []() { config(CH_DEPTH_FM); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu22Size = GET_MENU_SIZE(menu22);

const SerialMenuEntry menu23[] = {
  { item230, true, 'H', []() { config(CH_HEADING); }},
  { item231, true, 'O', []() { config(CH_OFF_COURSE); }},
  { item232, true, 'D', []() { config(CH_DR_COURSE); }},
  { item233, true, 'E', []() { config(CH_DR_DIST); }},
  { item234, true, 'C', []() { config(CH_COURSE); }},
  { item235, true, 'L', []() { config(CH_LEEWAY); }},
  { item236, true, 'T', []() { config(CH_TIDAL_SET); }},
  { item237, true, 'I', []() { config(CH_TIDAL_DRIFT); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu23Size = GET_MENU_SIZE(menu23);

const SerialMenuEntry menu24[] = {
  { item240, true, 'A', []() { config(CH_APP_WS_KT); }},
  { item241, true, 'T', []() { config(CH_TRUE_WS_KT); }},
  { item242, true, 'P', []() { config(CH_APP_WA); }},
  { item243, true, 'U', []() { config(CH_TRUE_WA); }},
  { item244, true, 'E', []() { config(CH_TW_DIR); }},
  { item245, true, 'H', []() { config(CH_HL_TREND); }},
  { item246, true, 'N', []() { config(CH_NEXT_LEG_AWA); }},
  { item247, true, 'X', []() { config(CH_NEXT_LEG_AWS); }},
  { item248, true, 'W', []() { config(CH_UPWASH); }},
  { item249, true, 'I', []() { config(CH_APP_WS_MS); }},
  { item24A, true, 'D', []() { config(CH_TRUE_WS_MS); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu24Size = GET_MENU_SIZE(menu24);

const SerialMenuEntry menu25[] = {
  { item250, true, 'T', []() { config(CH_TACK_PERF); }},
  { item251, true, 'E', []() { config(CH_REACH_PERF); }},
  { item252, true, 'O', []() { config(CH_OPT_WA); }},
  { item253, true, 'L', []() { config(CH_LAYLINE); }},
  { item254, true, 'H', []() { config(CH_HEEL_ANGLE); }},
  { item255, true, 'A', []() { config(CH_TGT_BOAT_SPD); }},
  { item256, true, 'P', []() { config(CH_HDG_NXT_TACK); }},
  { item257, true, 'I', []() { config(CH_FORE_AFT_TRM); }},
  { item258, true, 'M', []() { config(CH_MAST_ANGLE); }},
  { item259, true, 'S', []() { config(CH_WA_MAST); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu25Size = GET_MENU_SIZE(menu25);

const SerialMenuEntry menu26[] = {
  { item260, true, 'E', []() { config(CH_BRG_WP_WP_T); }},
  { item261, true, 'A', []() { config(CH_BRG_WP_WP_M); }},
  { item262, true, 'I', []() { config(CH_BRG_WP_RM_T); }},
  { item263, true, 'N', []() { config(CH_BRG_WP_RM_M); }},
  { item264, true, 'G', []() { config(CH_BRG_WP_GC_T); }},
  { item265, true, 'W', []() { config(CH_BRG_WP_GC_M); }},
  { item266, true, 'D', []() { config(CH_DST_WP_RM); }},
  { item267, true, 'S', []() { config(CH_DST_WP_GC); }},
  { item268, true, 'C', []() { config(CH_COG_T); }},
  { item269, true, 'O', []() { config(CH_COG_M); }},
  { item26A, true, 'P', []() { config(CH_SOG); }},
  { item26B, true, 'V', []() { config(CH_VMG_WP); }},
  { item26C, true, 'T', []() { config(CH_TIME_TO_WP); }},
  { item26D, true, 'K', []() { config(CH_CRS_TRK_ERR); }},
  { item26E, true, 'L', []() { config(CH_LATITUDE); }},
  { item26F, true, 'U', []() { config(CH_LONGITUDE); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu26Size = GET_MENU_SIZE(menu26);

const SerialMenuEntry menu27[] = {
  { item270, true, 'V', []() { config(CH_VOLTS); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu27Size = GET_MENU_SIZE(menu27);

const SerialMenuEntry menu28[] = {
  { item280, true, 'S', []() { config(CH_SEA_TEMP_F); }},
  { item281, true, 'T', []() { config(CH_SEA_TEMP_C); }},
  { item282, true, 'A', []() { config(CH_AIR_TEMP_F); }},
  { item283, true, 'C', []() { config(CH_AIR_TEMP_C); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu28Size = GET_MENU_SIZE(menu28);

const SerialMenuEntry menu29[] = {
  { item290, true, 'T', []() { config(CH_TIMER); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu29Size = GET_MENU_SIZE(menu29);

const SerialMenuEntry menu2A[] = {
  { item2A0, true, 'T', []() { config(CH_RUDDER_ANGLE); }},
  { item2A1, true, 'L', []() { config(CH_LINEAR_1); }},
  { item2A2, true, 'I', []() { config(CH_LINEAR_2); }},
  { item2A3, true, 'N', []() { config(CH_LINEAR_3); }},
  { item2A4, true, 'E', []() { config(CH_LINEAR_4); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu2ASize = GET_MENU_SIZE(menu2A);

const SerialMenuEntry menu2B[] = {
  { item2B0, true, 'F', []() { config(CH_FORESTAY); }},
  { item2B1, true, 'A', []() { config(CH_BACKSTAY); }},
  { item2B2, true, 'V', []() { config(CH_BOOM_VANG); }},
  { item2B3, true, 'I', []() { config(CH_INNER_FSTAY); }},
  { item2B4, true, 'H', []() { config(CH_INNER_FSTAY_HLYD); }},
  { item2B5, true, 'J', []() { config(CH_JIB_FURLER); }},
  { item2B5, true, 'Y', []() { config(CH_JIB_HYLD); }},
  { item2B6, true, 'O', []() { config(CH_OUTHAUL); }},
  { item2B7, true, 'C', []() { config(CH_CUNNINGHAM); }},
  { item2B8, true, 'Z', []() { config(CH_CODE_ZERO); }},
  { item2B9, true, 'S', []() { config(CH_BOBSTAY); }},
  { item2BA, true, 'M', []() { config(CH_MAINSHEET); }},
  { item2BB, true, 'P', []() { config(CH_PORT_RUNNER); }},
  { item2BC, true, 'T', []() { config(CH_STBD_RUNNER); }},
  { item2BD, true, 'D', []() { config(CH_PORT_DEFLECT); }},
  { item2BE, true, 'E', []() { config(CH_STBD_DEFLECT); }},
  { item2, true, 'B', []() { menu.load(menu2, menu2Size); menu.show(); }},
  { item1, true, 'R', []() { menu.show(); }},
};
constexpr uint8_t menu2BSize = GET_MENU_SIZE(menu2B);

void load_menu() {
  menu.load(menu0, menu0Size);
  menu.show();
}
