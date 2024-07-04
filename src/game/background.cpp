/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "background.hpp"

#include "../define.hpp"
#include "../dataTypes.hpp"
#include "../data/data.hpp"


//
MovingBackground::MovingBackground() {}


//
void MovingBackground::blit() const {
    // Filling background with light color
    data.setColor(FIELD_LIGHT);
    SDL_RenderClear(data.renderer);

    // Drawing dark parts of field
    data.setColor(FIELD_DARK);
    for (coord y = 0; y < SCREEN_HEIGHT / CELL_SIDE + 1; ++y) {
        for (coord x = 0; x < SCREEN_WIDTH / CELL_SIDE + 2; ++x) {
            // Drawing dark rects on odd cells
            SDL_Rect rect = {(x-1) * CELL_SIDE + offset/2, (y-1) * CELL_SIDE + offset/2, CELL_SIDE, CELL_SIDE};
            if ((x + y) % 2) {
                SDL_RenderFillRect(data.renderer, &rect);
            }

            // Setting seed for random, to save position and prevent jump
            srand((144 + index - x - 12 * y) % 208);
            // Drawing figure (if need)
            if (rand() % 5 == 0) {
                SDL_RenderCopy(data.renderer, data.textures[IMG_GAME_WHITE_PAWN + rand() % 12], NULL, &rect);
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
