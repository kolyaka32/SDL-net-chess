/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "singlePlayer.hpp"
#include "pauseCycle.hpp"

//
SinglePlayerGameCycle::SinglePlayerGameCycle()
: BaseCycle(MUS_MAIN_THEME), width(data.animations[0]->w), height(data.animations[0]->h) {
    prevFrameUpdate = SDL_GetTicks64() + 400;
}

// Resetting data after all animations
SinglePlayerGameCycle::~SinglePlayerGameCycle() {
    // Resetting title
    data.updateTitle();

    // Resetting volume
    Mix_VolumeMusic(data.musicVolume);

    // Resetting color for figures
    for (Uint8 i = IMG_GAME_WHITE_PAWN; i <= IMG_GAME_BLACK_KING; ++i) {
        SDL_SetTextureColorMod(data.textures[i], 0, 0, 0);
    }

    // Resetting music to menu theme
    data.playMusic(MUS_MENU_THEME);
}

// Getting mouse clicking
bool SinglePlayerGameCycle::getMouseInput() {
    if (settingButton.in(mouseX, mouseY)) {
        runCycle<PauseCycle>();
    } else if (exitButton.in(mouseX, mouseY)) {
        return true;
    }

    return false;
}

//
void SinglePlayerGameCycle::update() {
    // Checking, if need to change state
    if (SDL_GetTicks64() > prevFrameUpdate) {
        // Changing length until reach need width
        if (currentWidth < width) {
            // Increasing field width
            currentWidth++;

            // Waiting for full width
            if (currentWidth == width) {
                // Setting updated window title
                switch (data.language) {
                case LNG_ENGLISH:
                    SDL_SetWindowTitle(data.window, "You been rickrolled!");
                    break;

                case LNG_RUSSIAN:
                    SDL_SetWindowTitle(data.window, "Ты зарикролен!");
                    break;

                case LNG_GERMAN:
                    SDL_SetWindowTitle(data.window, "Schach на SDL");
                    break;

                case LNG_BELARUSIAN:
                    SDL_SetWindowTitle(data.window, "Шахматы на SDL");
                    break;
                }
                // Correcting music volume
                Mix_VolumeMusic(data.musicVolume);
                // Setting new music and volume back
                data.playMusic(MUS_SINGLEPLAYER);
            }
            // Correcting height
            currentHeight = height * currentWidth / width;
            // Correcting music volume
            Mix_VolumeMusic(data.musicVolume * currentWidth/currentWidth * currentWidth/currentWidth);
            // Setting timer to update
            prevFrameUpdate = SDL_GetTicks64() + (width - currentWidth)*5;
        } else {
            // Updating frame counter
            frame = (frame + 1) % data.animations[type]->count;
            prevFrameUpdate = SDL_GetTicks64() + data.animations[type]->delays[frame]/3;
        }
    }
}


// Drawing background with special board
void SinglePlayerGameCycle::draw() const {
    // Bliting background
    data.setColor(BLACK);
    SDL_RenderClear(data.renderer);

    // Drawing buttons
    settingButton.blit();
    exitButton.blit();

    // Getting pixels of current frame
    const Uint8* frameData = (Uint8*)data.animations[type]->frames[frame][0].pixels;
    const float cellLength = 8 * width / currentWidth;

    // Setting seed of createdfigures for random on each step
    srand(currentWidth);

    for (Uint16 y=0; y < currentHeight; ++y) {
        for (Uint16 x=0; x < currentWidth; ++x) {
            // Drawing need figure
            SDL_FRect dest = {x * cellLength + LETTER_LINE, y * cellLength  + 182, cellLength, cellLength};

            // Drawing rect for field
            if ((x+y)%2) {
                data.setColor(FIELD_LIGHT);
            } else {
                data.setColor(FIELD_DARK);
            }

            SDL_RenderFillRectF(data.renderer, &dest);

            // Checkig, if need to make free cell
            if (currentWidth == width || (rand() % width < currentWidth)) {
                SDL_Texture* curTexture = data.textures[IMG_GAME_BLACK_PAWN + rand() % 6];

                Uint16 caret = (x + y * width) * 4;

                SDL_SetTextureColorMod(curTexture, frameData[caret+2], frameData[caret+1], frameData[caret]);

                SDL_RenderCopyF(data.renderer, curTexture, NULL, &dest);
            }
        }
    }

    // Bliting all to screen
    data.render();
}
