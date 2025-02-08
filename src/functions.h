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

    Serial.printf("%d,%d:%d\n", x, y, position);

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

void quantum_particles(Engine * engine) {
  
    static CRGB color = CRGB::Red;
    static int16_t x[PARTICLES_COUNT], y[PARTICLES_COUNT];
    static bool first_run = true;
    if(first_run) {
        for(int i = 0; i < PARTICLES_COUNT; i++) {x[i] = 12; y[i] = 12;}
        first_run = false;
    } 

    for(int i = 0; i < PARTICLES_COUNT; i++) {

        uint16_t previous_x = x[i], previous_y = y[i];
        uint16_t position = pixel_map[translate(x[i], y[i])];
        engine->display[position] = CRGB::Black;        
        
        int quantum_seed[2] = {random(0, 100), random(0, 100)};
        float quantum_foam[2] = {quantum_seed[0] / 100.0, quantum_seed[1] / 100.0};

        float quantum_ratio = quantum_foam[0] * quantum_foam[1];

        int quantum_final = (quantum_ratio * (pot::two() * 12));

        switch (random(0, 8)) {
            case 0:
                x[i] = wrap(x[i] - quantum_final);
                break;
            case 1:
                y[i] = wrap(y[i] - quantum_final);
                break;
            case 2:
                y[i] = wrap(y[i] - quantum_final);
                x[i] = wrap(x[i] - quantum_final);
                break;
            case 3:
                x[i] = wrap(x[i] + quantum_final);
                y[i] = wrap(y[i] - quantum_final);
                break;
            case 4:
                x[i] = wrap(x[i] + quantum_final);
                y[i] = wrap(y[i] + quantum_final);
                break;
            case 5:
                x[i] = wrap(x[i] - quantum_final);
                y[i] = wrap(y[i] + quantum_final);
                break;
            case 6:
                x[i] = wrap(x[i] + quantum_final);
                break;
            case 7:
                y[i] = wrap(y[i] + quantum_final);
                break;
        }
        
        if(x[i] != 12 && y[i] != 12)
        if(random(0, 2) == 0) {
            if(x[i] > 12) x[i]--;
            else x[i]++;
            if(y[i] > 12) y[i]--;
            else y[i]++;
        }

        position = pixel_map[translate(x[i], y[i])];
        engine->display[position] = color;
        Serial.printf("%d,%d:%d\n", x[i], y[i], position);

        int dif_x = std::abs(previous_x - x[i]);
        int dif_y = std::abs(previous_y - y[i]);

        if(dif_x > 12 || dif_y > 12) {
            static int step = 0;
            step = (step + 1) % 3;
            switch(step) {
                case 0: color = CRGB::Red; break;
                case 1: color = CRGB::Red;  break;
                case 2: color = CRGB::Red;   break;
                default: color = CRGB::Red;
            }
        }

    }    

    FastLED.show();
}

void GameOfLife(Engine * engine) {

    static uint16_t total_cells = 0;
    static uint8_t neighbours[GRID_HEIGHT][GRID_WIDTH], decay_side_start, decay_sides_to_search;
    static bool cells[GRID_HEIGHT][GRID_WIDTH];
    static int decay_reg = 0;
    static bool pattern_detected = false, decay_anyway = false, new_value;
    
    static const bool assign_table[2][9] = {
        {0, 0, 0, 1, 0, 0, 0, 0, 0}, //dead
        {0, 0, 1, 1, 0, 0, 0, 0, 0} //alive
    };

    static CRGB color_table[4] = { CRGB::Black, CRGB::White, CRGB::Black, CRGB::White };
    color_table[1] = CHSV(total_cells, 255, 255);
    
    static bool first_run = true;
    if(first_run) { first_run = false;
    
        for(int x = 0; x < GRID_WIDTH; x++) 
        for(int y = 0; y < GRID_HEIGHT; y++) {
            cells[x][y] = random(0, 2);
            neighbours[x][y] = 0;
        }
    }

    static uint16_t x, y, z, end;
    x = 0, y = 0;

    //trace the edges first
    for(y = 0; y < GRID_HEIGHT; y++) {
        neighbours[x][y] = cells[wrap_x(x - 1)][wrap_y(y - 1)];
        neighbours[x][y] += cells[wrap_x(x - 1)][y];
        neighbours[x][y] += cells[wrap_x(x - 1)][wrap_y(y + 1)];
        
        neighbours[x][y] += cells[x][wrap_y(y + 1)];
        neighbours[x][y] += cells[x][wrap_y(y - 1)];

        neighbours[x][y] += cells[wrap_x(x + 1)][wrap_y(y - 1)];
        neighbours[x][y] += cells[wrap_x(x + 1)][y];
        neighbours[x][y] += cells[wrap_x(x + 1)][wrap_y(y + 1)];
    }
    x = GRID_WIDTH - 1;
    for(y = 0; y < GRID_HEIGHT; y++) {
        neighbours[x][y] = cells[wrap_x(x - 1)][wrap_y(y - 1)];
        neighbours[x][y] += cells[wrap_x(x - 1)][y];
        neighbours[x][y] += cells[wrap_x(x - 1)][wrap_y(y + 1)];
        
        neighbours[x][y] += cells[x][wrap_y(y + 1)];
        neighbours[x][y] += cells[x][wrap_y(y - 1)];

        neighbours[x][y] += cells[wrap_x(x + 1)][wrap_y(y - 1)];
        neighbours[x][y] += cells[wrap_x(x + 1)][y];
        neighbours[x][y] += cells[wrap_x(x + 1)][wrap_y(y + 1)];
    }

    y = 0;
    for(x = 1; x < GRID_WIDTH - 1; x++) {
        neighbours[x][y] = cells[x - 1][wrap_y(y - 1)];
        neighbours[x][y] += cells[x - 1][y];
        neighbours[x][y] += cells[x - 1][wrap_y(y + 1)];
        
        neighbours[x][y] += cells[x][wrap_y(y + 1)];
        neighbours[x][y] += cells[x][wrap_y(y - 1)];

        neighbours[x][y] += cells[x + 1][wrap_y(y - 1)];
        neighbours[x][y] += cells[x + 1][y];
        neighbours[x][y] += cells[x + 1][wrap_y(y + 1)];
    }
    y = GRID_WIDTH - 1;
    for(x = 1; x < GRID_WIDTH - 1; x++)  {
        neighbours[x][y] = cells[x - 1][wrap_y(y - 1)];
        neighbours[x][y] += cells[x - 1][y];
        neighbours[x][y] += cells[x - 1][wrap_y(y + 1)];
        
        neighbours[x][y] += cells[x][wrap_y(y + 1)];
        neighbours[x][y] += cells[x][wrap_y(y - 1)];

        neighbours[x][y] += cells[x + 1][wrap_y(y - 1)];
        neighbours[x][y] += cells[x + 1][y];
        neighbours[x][y] += cells[x + 1][wrap_y(y + 1)];
    }

    //then count the main body more effeciently
    for(x = 1; x < GRID_WIDTH -1; x++)    
    for(y = 1; y < GRID_HEIGHT -1; y++) {
        neighbours[x][y] = cells[x - 1][y - 1];
        neighbours[x][y] += cells[x - 1][y];
        neighbours[x][y] += cells[x - 1][y + 1];
        
        neighbours[x][y] += cells[x][y + 1];
        neighbours[x][y] += cells[x][y - 1];

        neighbours[x][y] += cells[x + 1][y - 1];
        neighbours[x][y] += cells[x + 1][y];
        neighbours[x][y] += cells[x + 1][y + 1];
    }

    total_cells = 0;

    for(x = 0; x < GRID_WIDTH; x++) 
    for(y = 0; y < GRID_HEIGHT; y++) {
        engine->display[pixel_map[fast_translate(x, y)]] = color_table[cells[x][y]];
        cells[x][y] = assign_table[cells[x][y]][neighbours[x][y]];
        total_cells += cells[x][y];
    }

    // static float pot_cache = pot::two();
    // static int pot_cache_counter = 0;

    // if(++pot_cache_counter == 100) {
    //     pot_cache_counter = 0;
    //     pot_cache = pot::two();
    // }

    static uint16_t beep_freq = TAP_BASE_FREQ;
    if(total_cells < GROW_POINT_START) {
        tone(SOUND_PIN_SOURCE, TONE_START + (total_cells * COUNT_FREQ_SCALE), 9);
        beep_freq += TAP_FREQ_BOOST;
    }
    else {
        tone(SOUND_PIN_SOURCE, TONE_START + (total_cells * COUNT_FREQ_SCALE), 10);
        beep_freq += TAP_FREQ_SINK;
    }

    #if TAP_FREQ_BOOST < 0
        if(beep_freq > TAP_BASE_FREQ) beep_freq = TAP_BASE_FREQ;
        if(beep_freq < TAP_FLOOR_FREQ) beep_freq = TAP_FLOOR_FREQ;
    #else
        if(beep_freq < TAP_BASE_FREQ) beep_freq = TAP_BASE_FREQ;
        if(beep_freq > TAP_FLOOR_FREQ) beep_freq = TAP_FLOOR_FREQ;
    #endif

    static int rx, ry;
    color_table[3] = CHSV(total_cells+180, 0x80, 255);
    //Serial.printf("total (%u)\n", total_cells);
    if(total_cells <= GROW_POINT_START) {
        tone(SOUND_PIN_SOURCE, beep_freq, 1);
        int spawn_per_frame = MAX_SPAWN_PER_FRAME; 
        while(total_cells < GROW_POINT_END && spawn_per_frame--) {
            for(;;) {
                rx = random(0, GRID_WIDTH);
                ry = random(0, GRID_HEIGHT);
                //Serial.printf("Looking at %u,%u to potentially spawn a cell\n", total_cells, rx, ry);
                if(cells[rx][ry]) continue;
                cells[rx][ry] = true;
                engine->display[pixel_map[fast_translate(rx, ry)]] = color_table[3];
                break;
            }
            total_cells++;
        }
    }

    while(decay_reg-- > 0) {//decay a point 
        //rx = random(0, GRID_WIDTH);
        //ry = random(0, GRID_HEIGHT);
        //if(pot::two() > 0.5) Serial.printf("Decaying point at %u %u\n", rx, ry);
        //cells[rx][ry] = 0;
    }

    static uint16_t cell_count_memory[FROZEN_BUFFER] = {0};
    static uint8_t cell_index = 0;

    cell_count_memory[cell_index] = total_cells;
    cell_index++;

    if(cell_index == FROZEN_BUFFER) cell_index = 0;

    static uint32_t low_count,high_count,pattern_buffer[3];
    low_count = NUM_LEDS, high_count = 0;

    pattern_detected = true;
    for(x = 0; x < FROZEN_BUFFER; x++) {
        if(cell_count_memory[x] < low_count) low_count = cell_count_memory[x];
        if(cell_count_memory[x] > high_count) high_count = cell_count_memory[x];
        if(x < 3) pattern_buffer[x] = cell_count_memory[x];
        else if(pattern_buffer[x%3] != cell_count_memory[x]) pattern_detected = false;
    }

    if(total_cells != 0 && (high_count - low_count) < FROZEN_DIFF) decay_anyway = true;
    if(high_count == low_count && total_cells != 0) decay_anyway = true;

    static uint64_t last_decay = 0;
    if(engine->meta.frame - last_decay > DECAY_FRAME_DELAY && (decay_anyway || pattern_detected && random(0, DECAY_CHANCE) == 1)) {
        last_decay = engine->meta.frame;
        decay_anyway = false;
        rx=random(0, GRID_WIDTH);
        ry=random(0, GRID_HEIGHT);
        if(cells[rx][ry]) {
            x = rx, y = ry;
            goto decay;
        }

        for(z = 1; z < GRID_WIDTH; z++) {

            decay_side_start = random(0, 5), decay_sides_to_search = 4;

            while(decay_sides_to_search-- > 0)
            switch(decay_side_start) {
                case 0: {
                    x = wrap(rx - z), y = wrap(ry - z), end = y + z + 2;
                    for(; y < end; y++) if(cells[x][wrap(y)]) goto decay;
                    decay_sides_to_search--;
                }

                case 1: {
                    x = wrap(rx + z), y = wrap(ry - z), end = y + z + 2;
                    for(; y < end; y++) if(cells[x][wrap(y)]) goto decay;
                    decay_sides_to_search--;
                }

                case 2: {
                    y = wrap(ry - z), x = wrap(rx - z + 1), end = z + z;
                    for(; x < end; x++) if(cells[wrap(x)][y]) goto decay;
                    decay_sides_to_search--;
                }

                case 3: {
                    y = wrap(ry + z), x = wrap(rx - z + 1), end = x + z;
                    for(; x < end; x++) if(cells[wrap(x)][y]) goto decay;    
                    decay_side_start = 0;
                    decay_sides_to_search--;
                }
            }
                  
        }

        decay: {
            for(rx = -1; rx < 2; rx++)
            for(ry = -1; ry < 2; ry++) {
                new_value = random(0, 2);
                cells[wrap(x+rx)][wrap(y+ry)] = new_value;
                engine->display[pixel_map[fast_translate(wrap(x+rx), wrap(y+ry))]] = color_table[new_value + 2];
            }

            tone(SOUND_PIN_SOURCE, 2700, 2);
            tone(SOUND_PIN_SOURCE, 900, 4);
            tone(SOUND_PIN_SOURCE, 300, 4);
        };
    }

    

    FastLED.show();
    engine->meta.frame++;

    if(pot::two() > 0.5) {
        Serial.printf("Total cells: %u\n", total_cells);
        delay(1000);
    }

}