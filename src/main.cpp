#include <Arduino.h>
#include "device.h"
#include "matrix.h"
#include "pots.h"

void setup () {
  Serial.begin(115200);
  device::setup();
  pot::setup();
  matrix::setup();
  matrix::set(matrix::gol);
}

void loop () {
//   static uint8_t state_id = 0;
//   state_id = (state_id + 1 ) % 3;
//   matrix::set(static_cast<matrix::simulation>(state_id));
  device::loop();
  matrix::loop();
  FastLED.setBrightness(pot::one() * 0xff);
}