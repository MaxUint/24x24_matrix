#pragma once
#include <Arduino.h>
#include <cmath>
#include "constants.h"
#include "pots.h"

void quantum_particle(Engine * engine) {
  
    static CRGB color = CRGB::Green;
    static int16_t x = 12, y = 12;
    uint16_t previous_x = x, previous_y = y;

    uint16_t position = pixel_map[translate(x, y)];
    engine->display[position] = color;
    FastLED.show();
    Serial.printf("%d,%d:%d\n", x, y, position);
    engine->display[position] = CRGB::Black;

    int quantum_seed[2] = {random(0, 100), random(0, 100)};
    float quantum_foam[2] = {quantum_seed[0] / 100.0, quantum_seed[1] / 100.0};

    float quantum_ratio = quantum_foam[0] * quantum_foam[1];

    int quantum_final = (quantum_ratio * (pot::two() * 12));

    switch (random(0, 8)) {
        case 0:
            x = wrap(x - quantum_final);
            break;
        case 1:
            y = wrap(y - quantum_final);
            break;
        case 2:
            y = wrap(y - quantum_final);
            x = wrap(x - quantum_final);
            break;
        case 3:
            x = wrap(x + quantum_final);
            y = wrap(y - quantum_final);
            break;
        case 4:
            x = wrap(x + quantum_final);
            y = wrap(y + quantum_final);
            break;
        case 5:
            x = wrap(x - quantum_final);
            y = wrap(y + quantum_final);
            break;
        case 6:
            x = wrap(x + quantum_final);
            break;
        case 7:
            y = wrap(y + quantum_final);
            break;
    }
    
    if(x != 12 && y != 12)
    if(random(0, 2) == 0) {
        if(x > 12) x--;
        else x++;
        if(y > 12) y--;
        else y++;
    }

    int dif_x = std::abs(previous_x - x);
    int dif_y = std::abs(previous_y - y);

    if(dif_x > 12 || dif_y > 12) {
        static int step = 0;
        step = (step + 1) % 3;
        switch(step) {
            case 0: color = CRGB::Green; break;
            case 1: color = CRGB::Blue;  break;
            case 2: color = CRGB::Red;   break;
            default: color = CRGB::Purple;
        }
    }
}
