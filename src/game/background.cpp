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
    for (coord y = SCREEN_HEIGHT / CELL_SIDE + 2; y > 0; --y) {
        for (coord x = SCREEN_WIDTH / CELL_SIDE + 2; x > 0; --x) {
            // Drawing dark rects on odd cells
            SDL_Rect rect = {(x-2) * CELL_SIDE + offset/2, (y-2) * CELL_SIDE + offset/2, CELL_SIDE, CELL_SIDE};
            if ((x + y) % 2) {
                SDL_RenderFillRect(data.renderer, &rect);
            }
            
            // Setting seed for random, to save position and prevent jump
            srand((index - x - 12 * y) % 240);
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
        if (index > 234) {
            index = 0;
        }
    }
}
