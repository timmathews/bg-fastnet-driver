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
#include <math.h>
#include <stdint.h>
#include "SerialMenu.hpp"
#include "fastnet.h"
#include "menu.h"
#include "repl.h"
#include "actions.h"

#define DEBUG 0
#define ENABLE 2

enum readstate_t { LOST, SEEKING, HEADER, FILLING, DATA };

readstate_t read_state = LOST;

uint8_t data[256] = { 0 };
uint8_t rbuf[256] = { 0 };
uint8_t *p = rbuf;
uint8_t *q = rbuf;
uint64_t time = 0;

Frame last_rec;
Fastnet *fastnet;

extern SerialMenu &menu = SerialMenu::get();

void process_frame() {
  char buf[32];

  Serial.print(last_rec.print());

  if(last_rec.command() == CM_SET_BACKLIGHT) {
    if(last_rec[0] == 0) Serial.println("Backlight Off");
    else if(last_rec[0] == 1) Serial.println("Backlight Low");
    else if(last_rec[0] == 2) Serial.println("Backlight Med");
    else if(last_rec[0] == 4) Serial.println("Backlight High");
  } else if(last_rec.command() == CM_CHANGE_PAGE) {
    Serial.print("Seq ID: ");
    Serial.println(last_rec[0]);
    if(last_rec[1] == 0) Serial.println("Next page");
    else if(last_rec[1] == 1) Serial.println("Previous page");
    else if(last_rec[1] == 0xff) Serial.println("Select page");
  } else if(last_rec.command() == CM_CURRENT_PAGE) {
    Serial.print("Seq ID: ");
    Serial.println(last_rec[0]);
    Serial.print("Page: ");
    Serial.println(last_rec[1]);
    fastnet->set_page(last_rec[1]);
    Serial.print("Channel: ");
    Channel::label(last_rec[2], buf);
    Serial.println(buf);
    Serial.print("Node: ");
    Node::name(last_rec[3], buf);
    Serial.println(buf);
    Serial.print("\nLabel: ");
    Serial.write(&last_rec[4], 8);
    Serial.print("\nUnits: ");
    Serial.write(&last_rec[12], 2);
  } else if(last_rec.command() == CM_HELLO) {
    fastnet->register_device(last_rec.from());
  }
}

void read() {
  static uint8_t l;

  digitalWrite(ENABLE, LOW);

  if(Serial1.available())
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);

  switch(read_state) {
    case LOST:
      if(!Serial1.available()) {
        read_state = SEEKING;
      } else if(Serial1.peek() == 0xff) {
        memset(rbuf, 0, 256);
        read_state = SEEKING;
      } else {
        Serial1.read();
      }

      break;
    case SEEKING:
      if(Serial1.available() > 4) {
        p = rbuf;
        q = rbuf;
        p += Serial1.readBytes(p, 5);

        if(fastnet->checksum(q, 5)) {
          read_state = LOST;
          break;
        }

        read_state = HEADER;
      }

      break;
    case HEADER:
      last_rec.set_header(q[0], q[1], q[2], q[3]);
      l = q[2];

      if(l == 0xff) {
        read_state = LOST;
        break;
      } else if(l == 0) {
        p = q;
        process_frame();
        read_state = SEEKING;
      } else {
        read_state = FILLING;
        time = millis();
        q += 5;
      }

      break;
    case FILLING:
      if(abs(millis() - time) > 1000) {
        read_state = SEEKING;
        break;
      }

      if(Serial1.available() > l)
        p += Serial1.readBytes(p, l + 1);

      if(p >= q + l)
        read_state = DATA;

      break;
    case DATA:
      read_state = SEEKING;
      last_rec.set_data(q);
      process_frame();

      break;
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ENABLE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);

  pause();

  fastnet = new Fastnet(0x2F);
  fastnet->who();
  delay(100);

  load_menu();
}

void loop() {
  static uint16_t depth = 0;
  static uint16_t boat_spd = 0;
  static int16_t awa = 0;
  static uint16_t aws = 0;

  if(in_repl()) {
    repl(data, [](uint8_t * d, int l) { fastnet->raw(d, l); });
  } else {
    menu.run(0);
  }

  if (!paused())
  {
    fastnet->depth(depth);
    delay(10);
    fastnet->app_wind(awa, aws);
    delay(10);
    fastnet->boat_speed(boat_spd);
    delay(10);
    fastnet->vmg(boat_spd * 0.333);
  }

  delay(100);
  read();

  boat_spd += 25;
  if(boat_spd > 9999) boat_spd = 0;

  depth += 25;
  if(depth > 9999) depth = 0;

  aws += 25;
  if(aws > 9999) aws = 0;

  if(awa > 1800) {
    awa = -1775;
  }
  awa += 25;
}
