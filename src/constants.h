#pragma once
#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN                 13
#define COLOR_ORDER             GRB
#define CHIPSET                 WS2811
#define NUM_LEDS                576
#define BRIGHTNESS              0x0F

#define POTPIN_POWER_1          25
#define POTPIN_POWER_2          27
#define POTPIN_GROUND_1         33
#define POTPIN_GROUND_2         26
#define POTPIN_INPUT_1          12
#define POTPIN_INPUT_2          14
#define SOUND_PIN_SINK          22
#define SOUND_PIN_SOURCE        23

#define PARTICLES_COUNT         500
#define GRID_WIDTH              24
#define GRID_HEIGHT             24

#define TAP_BASE_FREQ           6000
#define TAP_FREQ_BOOST          -25
#define TAP_FREQ_SINK           25
#define TAP_FLOOR_FREQ          5000

#define TONE_START              150
#define COUNT_FREQ_SCALE        1

#define GROW_POINT_START        0
#define GROW_POINT_END          100

#define FROZEN_DIFF 6
#define FROZEN_BUFFER 20
#define FROZEN_DECAY_AMOUNT 20

#define DECAY_CHANCE 0x40 //avoid anything below 0x2 as this is if(random(0, n) == 1)
#define MAX_SPAWN_PER_FRAME 20
#define DECAY_FRAME_DELAY 3

#define wrap(d) ((d+GRID_WIDTH)%GRID_WIDTH)
#define wrap_x(d) ((d+GRID_WIDTH)%GRID_WIDTH)
#define wrap_y(d) ((d+GRID_HEIGHT)%GRID_HEIGHT)
#define translate(x, y) (wrap_x(x) + (wrap_y(y)*GRID_HEIGHT))
#define fast_translate(x, y) (x + y*GRID_HEIGHT)

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

struct metadata {
    uint64_t frame;
};

struct Engine {
    Lifeform frame[2][24][24];
    CRGB display[NUM_LEDS];
    metadata meta;
};

 uint16_t pixel_map[NUM_LEDS];