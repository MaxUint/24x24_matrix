#pragma once
#include <Arduino.h>
#include "constants.h"

namespace pot {
    
    void setup () {
        pinMode(POTPIN_POWER_1, OUTPUT);  digitalWrite(POTPIN_POWER_1, HIGH);
        pinMode(POTPIN_POWER_2, OUTPUT);  digitalWrite(POTPIN_POWER_2, HIGH);
        pinMode(POTPIN_GROUND_1, OUTPUT); digitalWrite(POTPIN_GROUND_1, LOW);
        pinMode(POTPIN_GROUND_2, OUTPUT); digitalWrite(POTPIN_GROUND_2, LOW);
        pinMode(POTPIN_INPUT_1, INPUT);
        pinMode(POTPIN_INPUT_2, INPUT);
    }

    float one () {
        return map(analogRead(POTPIN_INPUT_1), 0, 4095, 0, 100) / 100.0;
    }

    float two () {
        return map(analogRead(POTPIN_INPUT_2), 0, 4095, 0, 100) / 100.0;
    }
};