#pragma once
#include "common.hpp"

#define CH_NODE_RESET   0x00
#define CH_RUDDER_ANGLE 0x0B
#define CH_LINEAR_5     0x0C
#define CH_LINEAR_6     0x0D
#define CH_LINEAR_7     0x0E
#define CH_LINEAR_8     0x0F

#define CH_LINEAR_9     0x10
#define CH_LINEAR_10    0x11
#define CH_LINEAR_11    0x12
#define CH_LINEAR_12    0x13
#define CH_LINEAR_13    0x14
#define CH_LINEAR_14    0x15
#define CH_LINEAR_15    0x16
#define CH_LINEAR_17    0x17
#define CH_AIR_TEMP_F   0x1C
#define CH_AIR_TEMP_C   0x1D
#define CH_SEA_TEMP_F   0x1E
#define CH_SEA_TEMP_C   0x1F

#define CH_HL_TREND     0x27
#define CH_OFF_COURSE   0x29

#define CH_TACK_PERF    0x32
#define CH_REACH_PERF   0x33
#define CH_HEEL_ANGLE   0x34
#define CH_OPT_WA       0x35
#define CH_DEPTH_GAIN   0x36
#define CH_DEPTH_NOISE  0x37
#define CH_LINEAR_1     0x38
#define CH_LINEAR_2     0x39
#define CH_LINEAR_3     0x3A
#define CH_LINEAR_4     0x3B
#define CH_RATE_MOTION  0x3C

#define CH_FORESTAY     0x40
#define CH_BOAT_SPD_KT  0x41
#define CH_BOAT_SPD_RAW 0x42
#define CH_LAT_LON      0x47
#define CH_HEADING      0x49
#define CH_HEADING_RAW  0x4A
#define CH_APP_WS_KT    0x4D
#define CH_APP_WS_RAW   0x4E
#define CH_APP_WS_MS    0x4F

#define CH_APP_WA       0x51
#define CH_APP_WA_RAW   0x52
#define CH_TARGET_TWA   0x53
#define CH_TRUE_WS_KT   0x55
#define CH_TRUE_WS_MS   0x56
#define CH_MEAS_WS_K    0x57
#define CH_TRUE_WA      0x59
#define CH_MEAS_WA      0x5A

#define CH_AVG_SPD      0x64
#define CH_KEEL_ANGLE   0x66
#define CH_CANARD_ANGLE 0x67
#define CH_TRM_TB_ANGLE 0x68
#define CH_COURSE       0x69
#define CH_TW_DIR       0x6D
#define CH_NEXT_LEG_AWA 0x6F

#define CH_NEXT_LEG_TBS 0x70
#define CH_NEXT_LEG_AWS 0x71
#define CH_TIMER        0x75
#define CH_ROLL_TIMER   0x77
#define CH_TGT_BOAT_SPD 0x7D
#define CH_VMG          0x7F

#define CH_DR_DIST      0x81
#define CH_LEEWAY       0x82
#define CH_TIDAL_DRIFT  0x83
#define CH_TIDAL_SET    0x84
#define CH_UPWASH       0x85
#define CH_BARO_TREND   0x86
#define CH_BARO_PRESS   0x87
#define CH_VOLTS        0x8D

#define CH_HDG_NXT_TACK 0x9A
#define CH_FORE_AFT_TRM 0x9B
#define CH_MAST_ANGLE   0x9C
#define CH_WA_MAST      0x9D
#define CH_PITCH_RATE   0x9E

#define CH_DBOARD_POS   0xA3
#define CH_BOOM_POS     0xA4

#define CH_COMPASSS_CAL 0xB3
#define CH_LATITUDE     0xBB
#define CH_LONGITUDE    0xBC

#define CH_DEPTH_M      0xC1
#define CH_DEPTH_FT     0xC2
#define CH_DEPTH_FM     0xC3
#define CH_STD_LOG      0xCD
#define CH_TRIP_LOG     0xCF

#define CH_DR_COURSE    0xD3
#define CH_LOCAL_TIME   0xDC

#define CH_BRG_WP_WP_T  0xE0
#define CH_BRG_WP_WP_M  0xE1
#define CH_LAYLINE      0xE2
#define CH_BRG_WP_RM_T  0xE3
#define CH_BRG_WP_RM_M  0xE4
#define CH_BRG_WP_GC_T  0xE5
#define CH_BRG_WP_GC_M  0xE6
#define CH_DST_WP_RM    0xE7
#define CH_DST_WP_GC    0xE8
#define CH_COG_T        0xE9
#define CH_COG_M        0xEA
#define CH_SOG          0xEB
#define CH_VMG_WP       0xEC
#define CH_TIME_TO_WP   0xED
#define CH_CRS_TRK_ERR  0xEE
#define CH_REMOTE_0     0xEF

#define CH_REMOTE_1     0xF0
#define CH_REMOTE_2     0xF1
#define CH_REMOTE_3     0xF2
#define CH_REMOTE_4     0xF3
#define CH_REMOTE_5     0xF4
#define CH_REMOTE_6     0xF5
#define CH_REMOTE_7     0xF6
#define CH_REMOTE_8     0xF7
#define CH_REMOTE_9     0xF8
#define CH_DIST_NXT_WP  0xFA
#define CH_TIME_TO_LYLN 0xFB

#define CH_BACKSTAY         0x011A
#define CH_BOOM_VANG        0x011B
#define CH_INNER_FSTAY      0x011E
#define CH_INNER_FSTAY_HLYD 0x011F

#define CH_JIB_FURLER 0x0120
#define CH_JIB_HYLD   0x0121
#define CH_OUTHAUL    0x0122
#define CH_CUNNINGHAM 0x0124
#define CH_CODE_ZERO  0x012A

#define CH_BOBSTAY     0x0154
#define CH_MAINSHEET   0x0159
#define CH_PORT_RUNNER 0x015C
#define CH_STBD_RUNNER 0x015D

#define CH_PORT_DEFLECT 0x0162
#define CH_STBD_DEFLECT 0x0163

const char PROGMEM ch00[] = "Node Reset";
const char PROGMEM ch0B[] = "RUDDER  % ";
const char PROGMEM ch10[] = "LINEAR 5  ";
const char PROGMEM ch11[] = "LINEAR 6  ";
const char PROGMEM ch12[] = "LINEAR 7  ";
const char PROGMEM ch13[] = "LINEAR 8  ";
const char PROGMEM ch14[] = "LINEAR 9  ";
const char PROGMEM ch15[] = "LINEAR 10 ";
const char PROGMEM ch16[] = "LINEAR 11 ";
const char PROGMEM ch17[] = "LINEAR 12 ";
const char PROGMEM ch18[] = "LINEAR 13 ";
const char PROGMEM ch19[] = "LINEAR 14 ";
const char PROGMEM ch1A[] = "LINEAR 15 ";
const char PROGMEM ch1B[] = "LINEAR 16 ";
const char PROGMEM ch1C[] = "AIR TEMP%F";
const char PROGMEM ch1D[] = "AIR TEMP%C";
const char PROGMEM ch1E[] = "SEA TEMP%F";
const char PROGMEM ch1F[] = "SEA TEMP%C";

const char PROGMEM ch27[] = "LIFT/HDR% ";
const char PROGMEM ch29[] = "OFF CRSE% ";
const char PROGMEM ch2E[] = "  NMEA    ";

const char PROGMEM ch32[] = "TACKING PC";
const char PROGMEM ch33[] = "REACHINGPC";
const char PROGMEM ch34[] = "   HEEL % ";
const char PROGMEM ch35[] = "OPT W/A % ";
const char PROGMEM ch36[] = "GAIN    DB";
const char PROGMEM ch37[] = "NOISE   DB";
const char PROGMEM ch38[] = "LINEAR 1  ";
const char PROGMEM ch39[] = "LINEAR 2  ";
const char PROGMEM ch3A[] = "LINEAR 3  ";
const char PROGMEM ch3B[] = "LINEAR 4  ";
const char PROGMEM ch3C[] = "ROLLRATE%S";

const char PROGMEM ch40[] = "FORESTAYT ";
const char PROGMEM ch41[] = "BOAT SPDKT";
const char PROGMEM ch42[] = "Boat Speed Raw";
const char PROGMEM ch44[] = "YAW RATE%S";
const char PROGMEM ch47[] = "Lat/Lon   "; // Not in H3000 manual
const char PROGMEM ch49[] = "HEADING %M";
const char PROGMEM ch4A[] = "Heading Raw";
const char PROGMEM ch4D[] = "APP W/S KT";
const char PROGMEM ch4E[] = "APP W/S Raw";
const char PROGMEM ch4F[] = "APP W/S MS";

const char PROGMEM ch51[] = "APP W/A % ";
const char PROGMEM ch52[] = "APP W/A Raw";
const char PROGMEM ch53[] = "TARG TWA %";
const char PROGMEM ch55[] = "TRUE W/SKT";
const char PROGMEM ch56[] = "TRUE W/SMS";
const char PROGMEM ch57[] = "MEAS W/SKT";
const char PROGMEM ch59[] = "TRUE W/A% ";
const char PROGMEM ch5A[] = "MEAS W/A% ";

const char PROGMEM ch64[] = "AVG SPD KT";
const char PROGMEM ch66[] = "KEEL ANG% ";
const char PROGMEM ch67[] = "CANARD  % ";
const char PROGMEM ch68[] = "TRIM TAB% ";
const char PROGMEM ch69[] = "COURSE  %M";
const char PROGMEM ch6D[] = "TRUE DIR%M";
const char PROGMEM ch6F[] = "N/L AWA % ";

const char PROGMEM ch70[] = "N/L SPD KT";
const char PROGMEM ch71[] = "N/L AWS KT";
const char PROGMEM ch75[] = "TIMER   MS";
const char PROGMEM ch77[] = "Rolling Timer"; // Not in H3000 manual
const char PROGMEM ch7C[] = "POL SPD KT";
const char PROGMEM ch7D[] = "TARG SPDKT";
const char PROGMEM ch7E[] = "POL PERFPC";
const char PROGMEM ch7F[] = "  VMG   KT";

const char PROGMEM ch81[] = "D/R DISTNM";
const char PROGMEM ch82[] = "LEEWAY  % ";
const char PROGMEM ch83[] = "TIDE RTEKT";
const char PROGMEM ch84[] = "TIDE SET%M";
const char PROGMEM ch85[] = "  UPWASH  "; // Not in H3000 manual, in 2020 F/W
const char PROGMEM ch86[] = "PR TRENDMB";
const char PROGMEM ch87[] = "BAROMETRMB";
const char PROGMEM ch8D[] = "VOLTS    V";

const char PROGMEM ch98[] = "S/L DISTFT";
const char PROGMEM ch9A[] = "OPP TACK%M";
const char PROGMEM ch9B[] = " TRIM   % ";
const char PROGMEM ch9C[] = "MAST ANG% ";
const char PROGMEM ch9D[] = "W/A MAST% ";
const char PROGMEM ch9E[] = "PTCHRATE%S";

const char PROGMEM chA3[] = "DAGGERBD  ";
const char PROGMEM chA4[] = "BOOM POS  ";

const char PROGMEM chB2[] = "COMP CAL% "; // Not in H3000 manual
const char PROGMEM chB7[] = "CURRENT A ";
const char PROGMEM chB9[] = "MOB BRG % ";
const char PROGMEM chBA[] = "MOB RNG NM";
const char PROGMEM chBB[] = "LATITUDE  ";
const char PROGMEM chBC[] = "LONGITUDE ";

const char PROGMEM chC1[] = "DEPTH   M ";
const char PROGMEM chC2[] = "DEPTH   FT";
const char PROGMEM chC3[] = "DEPTH   FM";
const char PROGMEM chC7[] = "AFT DPTHM ";
const char PROGMEM chCD[] = "STD LOG NM";
const char PROGMEM chCF[] = "TRIP LOGNM";

const char PROGMEM chD3[] = "D/R CRSE%M";
const char PROGMEM chDC[] = "LOC TIMEMS";

const char PROGMEM chE0[] = "BRG W-W %T";
const char PROGMEM chE1[] = "BRG W-W %M";
const char PROGMEM chE2[] = "LAYLINE NM";
const char PROGMEM chE3[] = "BTW RMB %T";
const char PROGMEM chE4[] = "BTW RMB %M";
const char PROGMEM chE5[] = "BTW GC  %T";
const char PROGMEM chE6[] = "BTW GC  %M";
const char PROGMEM chE7[] = "DTW RMB NM";
const char PROGMEM chE8[] = "DTW GC  NM";
const char PROGMEM chE9[] = "CRSE O/G%T";
const char PROGMEM chEA[] = "CRSE O/G%M";
const char PROGMEM chEB[] = "SPD O/G KT";
const char PROGMEM chEC[] = "VMG WPT KT";
const char PROGMEM chED[] = "TTG WPT MS";
const char PROGMEM chEE[] = "CROSS TRNM";
const char PROGMEM chEF[] = "REMOTE 0  ";

const char PROGMEM chF0[] = "REMOTE 1  ";
const char PROGMEM chF1[] = "REMOTE 2  ";
const char PROGMEM chF2[] = "REMOTE 3  ";
const char PROGMEM chF3[] = "REMOTE 4  ";
const char PROGMEM chF4[] = "REMOTE 5  ";
const char PROGMEM chF5[] = "REMOTE 6  ";
const char PROGMEM chF6[] = "REMOTE 7  ";
const char PROGMEM chF7[] = "REMOTE 8  ";
const char PROGMEM chF8[] = "REMOTE 9  ";
const char PROGMEM chFA[] = "NEXT WPTNM";
const char PROGMEM chFB[] = "TIME L/LMS";

const char PROGMEM cn04[] = "TTW L/L MS";
const char PROGMEM cn05[] = "DTW L/L NM";

const char PROGMEM cn10[] = "S/L BRG % ";
const char PROGMEM cn11[] = "S/L BIAS  ";
const char PROGMEM cn12[] = "S/L PORTFT";
const char PROGMEM cn13[] = "S/L STBDFT";
const char PROGMEM cn18[] = "BOAT LENFT";
const char PROGMEM cn19[] = "S/L DISTBL";
const char PROGMEM cn1A[] = "BACKSTAYT ";
const char PROGMEM cn1B[] = "  VANG  T ";
const char PROGMEM cn1C[] = "CHAIN   FT";
const char PROGMEM cn1D[] = "VMG PERFPC";
const char PROGMEM cn1E[] = "INFSTY  T ";
const char PROGMEM cn1F[] = "INFSTY HT ";

const char PROGMEM cn20[] = "JIB F   T ";
const char PROGMEM cn21[] = "JIB H   T ";
const char PROGMEM cn22[] = "OUTHAUL T ";
const char PROGMEM cn23[] = "PLOW    % ";
const char PROGMEM cn24[] = "CUNINGHMT ";
const char PROGMEM cn29[] = "BOOM ANG% ";
const char PROGMEM cn2A[] = "CODEZEROT ";

const char PROGMEM cn30[] = "MAG VAR % ";
const char PROGMEM cn32[] = "OPP COG %M";
const char PROGMEM cn33[] = "OPP HDG %M";
const char PROGMEM cn34[] = "MST RAKE% ";
const char PROGMEM cn35[] = "N/L BRG %M";
const char PROGMEM cn36[] = "N/L TBS KT";
const char PROGMEM cn37[] = "GWD     %M";
const char PROGMEM cn38[] = "GWS     KT";
const char PROGMEM cn39[] = "MST CANT% ";
const char PROGMEM cn3A[] = "RUD TOE % ";
const char PROGMEM cn3B[] = "DAGGER P  ";
const char PROGMEM cn3C[] = "DAGGER S  ";

const char PROGMEM cn54[] = "BOBSTAY T ";
const char PROGMEM cn55[] = "J1 LOAD T ";
const char PROGMEM cn56[] = "J2 LOAD T ";
const char PROGMEM cn57[] = "J3 LOAD T ";
const char PROGMEM cn58[] = "MASTBASET ";
const char PROGMEM cn59[] = "MAINSHETT ";
const char PROGMEM cn5A[] = "D0 PORT   ";
const char PROGMEM cn5B[] = "D0 STBD   ";
const char PROGMEM cn5C[] = "RUNNER PT ";
const char PROGMEM cn5D[] = "RUNNER ST ";
const char PROGMEM cn5E[] = "FOIL S  T ";
const char PROGMEM cn5F[] = "FOIL P  T ";

const char PROGMEM cn62[] = "DFLCT P T ";
const char PROGMEM cn63[] = "DFLCT S T ";
const char PROGMEM cn64[] = "RUDDER PT ";
const char PROGMEM cn65[] = "RUDDER ST ";
const char PROGMEM cn66[] = "D1 PORT   ";
const char PROGMEM cn67[] = "D1 STBD   ";
const char PROGMEM cn68[] = "V0 PORT   ";
const char PROGMEM cn69[] = "V0 STBD   ";
const char PROGMEM cn6A[] = "V1 PORT   ";
const char PROGMEM cn6B[] = "V1 STBD   ";

const char *const PROGMEM channels[] = {
  ch00, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, ch0B, unkn, unkn, unkn, unkn,
  ch10, ch11, ch12, ch13, ch14, ch15, ch16, ch17, ch18, ch19, ch1A, ch1B, ch1C, ch1D, ch1E, ch1F,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, ch27, unkn, ch29, unkn, unkn, unkn, unkn, ch2E, unkn,
  unkn, unkn, ch32, ch33, ch34, ch35, ch36, ch37, ch38, ch39, ch3A, ch3B, ch3C, unkn, unkn, unkn,
  ch40, ch41, ch42, unkn, ch44, unkn, unkn, ch47, unkn, ch49, ch4A, unkn, unkn, ch4D, ch4E, ch4F,
  unkn, ch51, ch52, ch53, unkn, ch55, ch56, ch57, unkn, ch59, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, ch64, unkn, ch66, ch67, ch68, ch69, unkn, unkn, unkn, ch6D, unkn, ch6F,
  ch70, ch71, unkn, unkn, unkn, ch75, unkn, ch77, unkn, unkn, unkn, unkn, ch7C, ch7D, ch7E, ch7F,
  unkn, ch81, ch82, ch83, ch84, ch85, ch86, ch87, unkn, unkn, unkn, unkn, unkn, ch8D, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, ch98, unkn, ch9A, ch9B, ch9C, ch9D, ch9E, unkn,
  unkn, unkn, unkn, chA3, chA4, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, chB2, unkn, unkn, unkn, unkn, chB7, unkn, chB9, chBA, chBB, chBC, unkn, unkn, unkn,
  unkn, chC1, chC2, chC3, unkn, unkn, unkn, chC7, unkn, unkn, unkn, unkn, unkn, chCD, unkn, chCF,
  unkn, unkn, unkn, chD3, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, chDC, unkn, unkn, unkn,
  chE0, chE1, chE2, chE3, chE4, chE5, chE6, chE7, chE8, chE9, chEA, chEB, chEC, chED, chEE, chEF,
  chF0, chF1, chF2, chF3, chF4, chF5, chF6, chF7, chF8, unkn, chFA, chFB, unkn, unkn, unkn, unkn,
};

const char *const PROGMEM channels_2[] = {
  ch00, unkn, unkn, unkn, cn04, cn05, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  cn10, cn11, cn12, cn13, unkn, unkn, unkn, unkn, cn18, cn19, cn1A, cn1B, cn1C, cn1D, cn1E, cn1F,
  cn20, cn21, cn22, cn23, cn24, unkn, unkn, unkn, unkn, cn29, cn2A, unkn, unkn, unkn, unkn, unkn,
  cn30, unkn, cn32, cn33, cn34, cn35, cn36, cn37, cn38, cn39, cn3A, cn3B, cn3C, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn, unkn,
  unkn, unkn, unkn, unkn, unkn, cn55, cn56, cn57, cn58, cn59, cn5A, cn5B, cn5C, cn5D, cn5E, cn5F,
  unkn, unkn, cn62, cn63, cn64, cn65, cn66, cn67, cn68, cn69, cn6A, cn6B, unkn, unkn, unkn, unkn,
};

class Channel {
private:
  Channel();

public:
  static void label(uint16_t code, char *buf);
};
