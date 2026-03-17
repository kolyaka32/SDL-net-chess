/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "singleplayerGame.hpp"


SinglePlayerGameCycle::SinglePlayerGameCycle(Window& _window)
: BaseCycle(_window),
startVolume(audio.music.getVolume()),
animation(_window.getAnimation(Animations::SinglePlayer)),
width(animation->w),
height(animation->h) {
    prevFrameUpdate = getTime() + 400;

    // Starting main song (if wasn't started)
    if(!isRestarted()) {
        audio.music.start(Music::Main);
    }
}

SinglePlayerGameCycle::~SinglePlayerGameCycle() {
    // Resetting title
    window.updateTitle();

    // Resetting volume
    audio.music.setVolume(startVolume);

    // Resetting color for figures
    for (Textures i = Textures::WhitePawn; i <= Textures::BlackKing; i=i+1) {
        window.setColorMode(window.getTexture(i));
    }
}

bool SinglePlayerGameCycle::inputMouseDown() {
    if (BaseCycle::inputMouseDown()) {
        // Correcting volume (if have any changes)
        if (currentWidth != width) {
            startVolume = audio.music.getVolume();
            audio.music.setVolume(startVolume * (width-currentWidth)/width);
        }
        return true;
    }
    return false;
}

void SinglePlayerGameCycle::update() {
    BaseCycle::update();

    // Checking, if need to change state
    if (getTime() > prevFrameUpdate) {
        // Changing length until reach need width
        if (currentWidth < width) {
            // Increasing field width
            currentWidth++;

            // Waiting for full width
            if (currentWidth == width) {
                // Setting updated window title
                window.setTitle({"You been rickrolled!","Ты зарикролен!","Schach на SDL","Шахматы на SDL"});

                // Setting new music and volume back
                audio.music.setVolume(startVolume);
                audio.music.start(Music::Singleplayer);
                return;
            }
            // Correcting height
            currentHeight = height * currentWidth / width;
            // Correcting music volume
            audio.music.setVolume(startVolume * (width-currentWidth)/width);

            // Setting timer to update
            prevFrameUpdate = getTime() + (width - currentWidth)*5;
        } else {
            // Updating frame counter
            frame = (frame + 1) % animation->count;
            prevFrameUpdate = getTime() + animation->delays[frame]/3;
        }
    }
}

void SinglePlayerGameCycle::draw() const {
    // Bliting background
    window.setDrawColor(BLACK);
    window.clear();

    // Drawing buttons
    exitButton.blit();

    // Getting pixels of current frame
    const Uint8* frameData = (Uint8*)animation->frames[frame][0].pixels;
    const float cellLength = 8 * width / currentWidth;

    // Setting seed of createdfigures for random on each step
    srand(currentWidth);

    for (Uint16 y=0; y < currentHeight; ++y) {
        for (Uint16 x=0; x < currentWidth; ++x) {
            // Drawing need figure
            SDL_FRect dest = {x * cellLength + LETTER_LINE, y * cellLength  + 182, cellLength, cellLength};

            // Drawing rect for field
            if ((x+y)%2) {
                window.setDrawColor(FIELD_LIGHT);
            } else {
                window.setDrawColor(FIELD_DARK);
            }
            
            window.drawRect(dest);

            // Checkig, if need to make free cell
            if (currentWidth == width || (rand() % width < currentWidth)) {
                SDL_Texture* curTexture = window.getTexture(Textures::BlackPawn + rand() % 6);

                Uint16 caret = (x + y * width) * 4;

                window.setColorMode(curTexture, {frameData[caret+2], frameData[caret+1], frameData[caret]});

                window.blit(curTexture, dest);
            }
        }
    }
    // Drawing settings
    settings.blit();

    // Bliting all to screen
    window.render();
}
