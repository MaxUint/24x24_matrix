#include <Arduino.h>
#include <FastLED.h>
#include "functions.h"
#include "constants.h"
#include "pots.h"

namespace matrix {

    Engine engine;

    enum simulation {
        particle,
        atomic,
        gol
    };

    simulation state;

    void set(simulation new_state) {
        state = new_state;
    }

    void setup () {
        FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(engine.display, NUM_LEDS).setCorrection( TypicalLEDStrip );
        FastLED.setBrightness( BRIGHTNESS );

        int pixel = 0;
        
        for(int y = 0; y < 8; y++)
        for(int x = 0; x < 24; x++) 
            pixel_map[pixel++] = 575 - (x * 8) - y;

        for(int y = 0; y < 8; y++)
        for(int x = 0; x < 24; x++)
            pixel_map[pixel++] = 383 - (x * 8) - y;

        for(int y = 0; y < 8; y++)
        for(int x = 0; x < 24; x++)
            pixel_map[pixel++] = 191 - (x * 8) - y;

        engine.meta.frame = 0;
    
    }

    void loop () {
        switch(state) {
            case particle: quantum_particle(&engine); break;
            case atomic:    quantum_particles(&engine); break;
            case gol: GameOfLife(&engine); break;
            default: Serial.println("This isn't a display mode!");
        }
        
    }

};