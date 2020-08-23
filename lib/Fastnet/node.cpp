#include "node.hpp"
#include "string.h"

void Node::name(uint8_t a, char *buf) {
  if(a >= DEPTH_CPU && a < WIND_CPU) {
    strcpy_P(buf, node_depth);
  } else if(a >= WIND_CPU && a < PERF_CPU) {
    strcpy_P(buf, node_wind);
  } else if(a >= PERF_CPU && a < EXP_01) {
    strcpy_P(buf, node_perf);
  } else if(a == EXP_01) {
    strcpy_P(buf, node_exp_1);
  } else if(a == EXP_02) {
    strcpy_P(buf, node_exp_2);
  } else if(a == HALCYON_CPU) {
    strcpy_P(buf, node_halcyon);
  } else if(a >= H2000_GYRO && a < ACP_GYRO) {
    strcpy_P(buf, node_h2k_gyro);
  } else if(a >= ACP_GYRO && a < FFD) {
    strcpy_P(buf, node_acp_gyro);
  } else if(a >= FFD && a < HALCYON_FFD) {
    strcpy_P(buf, node_ffd);
  } else if(a >= HALCYON_FFD && a < D2020) {
    strcpy_P(buf, node_halcyon_ffd);
  } else if(a >= D2020 && a < PILOT) {
    strcpy_P(buf, node_2020);
  } else if(a >= PILOT && a < NMEA) {
    strcpy_P(buf, node_pilot);
  } else if(a >= NMEA && a < WIRELESS) {
    strcpy_P(buf, node_nmea);
  } else if(a == WIRELESS) {
    strcpy_P(buf, node_wireless);
  } else if(a >= LOADCELL && a < TANK_LEVEL) {
    strcpy_P(buf, node_loadcell);
  } else if(a == TANK_LEVEL) {
    strcpy_P(buf, node_tank);
  } else if(a == ALL_2020) {
    strcpy_P(buf, group_2020);
  } else if(a == ALL_H_FFD) {
    strcpy_P(buf, group_h_ffd);
  } else if(a == ALL_P_FFD) {
    strcpy_P(buf, group_p_ffd);
  } else if(a == ALL_CPU) {
    strcpy_P(buf, group_cpu);
  } else if(a == ALL_FFD) {
    strcpy_P(buf, group_ffd);
  } else if(a == BROADCAST) {
    strcpy_P(buf, broadcast);
  } else {
    strcpy_P(buf, unkn);
  }
}
