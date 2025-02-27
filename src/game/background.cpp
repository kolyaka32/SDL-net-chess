/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "background.hpp"

#include "../define.hpp"

// Static class members
Uint16 MovingBackground::offset = 0;   // Offset (in pixels) for moving background
Uint8 MovingBackground::index = 0;     // Index of drawing line (for figures)

MovingBackground::MovingBackground() {}

void MovingBackground::blit(const Window& _target) const {
    // Filling background with light color
    _target.setDrawColor(FIELD_LIGHT);
    _target.clear();

    // Drawing dark parts of field
    _target.setDrawColor(FIELD_DARK);
    for (Uint8 y = 0; y < SCREEN_HEIGHT / CELL_SIDE + 1; ++y) {
        for (Uint8 x = 0; x < SCREEN_WIDTH / CELL_SIDE + 2; ++x) {
            // Drawing dark rects on odd cells
            SDL_FRect rect = {float((x-1)*CELL_SIDE + offset/2.0), float((y-1) * CELL_SIDE + offset/2), CELL_SIDE, CELL_SIDE};
            if ((x + y) % 2) {
                _target.drawRect(rect);
            }

            // Setting seed for random, to save position and prevent jump
            srand((144 + index - x - 12 * y) % 208);
            // Drawing figure (if need)
            if (rand() % 5 == 0) {
                _target.blit(IMG_names(IMG_GAME_WHITE_PAWN + rand() % 12), rect);
            }
        }
    }
}

//
void MovingBackground::update() {
    // Changing offset (moving background)
    offset++;

    // Resetting offset for move forward
    if (offset > CELL_SIDE * 2) {
        offset = 0;
        index += 13;
        if (index >= 208) {
            index = 0;
        }
    }
}
