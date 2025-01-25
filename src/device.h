#pragma once
#include <Arduino.h>
#include <esp_task_wdt.h>

namespace device {

  void logic ();
  void light ();
  bool visible = true;

  enum state {
    normal,
    sensor_error,
    setting_up,
    off,
  };

  state code = state::setting_up;

  uint32_t on_delay [] = {
    250,
    500,
    250,
    1000,
  };

  uint32_t off_delay [] = {
    2750,
    500,
    50,
    1000,
  };

  void setup () {
    esp_task_wdt_init(60, true);
    esp_task_wdt_add(NULL);

    pinMode(LED_BUILTIN, OUTPUT);

    Serial.print("TX:   ");   Serial.println(TX);
    Serial.print("RX:   ");   Serial.println(RX);

    Serial.print("MOSI: ");   Serial.println(MOSI);
    Serial.print("MISO: ");   Serial.println(MISO);
    Serial.print("SCK:  ");   Serial.println(SCK);
    Serial.print("SS:   ");   Serial.println(SS);

    Serial.print("SDA:  ");   Serial.println(SDA);
    Serial.print("SCL:  ");   Serial.println(SCL);

    while(millis() < 1000) light();
    code = state::normal;
  }

  void reboot () {
    Serial.println("Rebooting");
    for(;;) delayMicroseconds(1000);
  }

  void light () {
    uint32_t span = on_delay[code] + off_delay[code];
    uint32_t portion = millis() % span;
    bool light_on = portion < on_delay[code];
    if(visible == false) light_on = false;

    digitalWrite(LED_BUILTIN, light_on);
  }

  void flash () {
    light();
  }

  void loop () {
    esp_task_wdt_reset();
    light();
    logic();
  }

  void logic () {
    static state last_code = code;
    static uint32_t last_change = 0;

    if(code != last_code) {
      last_change = millis();
      last_code = code;
    }

    uint32_t state_duration = millis() - last_change;

    if(code == state::sensor_error && state_duration > 5000) reboot();

  }

}