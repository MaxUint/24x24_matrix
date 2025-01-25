#pragma once
#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     13
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    576
#define BRIGHTNESS  0x0F
#define wrap(d) ((d+24)%24)
#define translate(x, y) (wrap(x) + (wrap(y)*24))
#define NUM_LEDS    576

#define POTPIN_POWER_1 25
#define POTPIN_POWER_2 27
#define POTPIN_GROUND_1 33
#define POTPIN_GROUND_2 26
#define POTPIN_INPUT_1 12
#define POTPIN_INPUT_2 14


enum Type {
    plant,
    snail,
    shrimp,
    algea
};

struct Lifeform {
    Type type;
    uint8_t age;
    uint8_t health;
    uint8_t mana;
    uint8_t shell;
};

struct Engine {
    Lifeform frame[2][24][24];
    CRGB display[NUM_LEDS];
};

 uint16_t pixel_map[NUM_LEDS];