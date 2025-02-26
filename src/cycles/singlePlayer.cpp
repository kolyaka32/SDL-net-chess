/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "singlePlayer.hpp"


SinglePlayerGameCycle::SinglePlayerGameCycle(App& _app)
: BaseCycle(_app),
app(_app),
width(0/*data.animations[0]->w*/),
height(0/*data.animations[0]->h*/) {
    prevFrameUpdate = getTime() + 400;

    // Starting menu song (if wasn't started)
    if(!isRestarted()) {
        _app.music.start(MUS_MENU);
    }
}

SinglePlayerGameCycle::~SinglePlayerGameCycle() {
    // Resetting title
    app.window.updateTitle();

    // Resetting volume
    //Mix_VolumeMusic(data.musicVolume);

    // Resetting color for figures
    for (unsigned i = IMG_GAME_WHITE_PAWN; i <= IMG_GAME_BLACK_KING; ++i) {
        SDL_SetTextureColorMod(app.window.getTexture(IMG_names(i)), 0, 0, 0);
    }
}

void SinglePlayerGameCycle::getMouseInput(App& _app) {
    // Checking on exit
    if (exitButton.in(mouseX, mouseY)) {
        _app.startNextCycle(CYCLE_MENU);
        stop();
        return;
    }
    // Clicking in settings menu
    settings.click(mouseX, mouseY);
    return;
}

void SinglePlayerGameCycle::update(App& _app) {
    // Checking, if need to change state
    if (getTime() > prevFrameUpdate) {
        // Changing length until reach need width
        if (currentWidth < width) {
            // Increasing field width
            currentWidth++;

            // Waiting for full width
            if (currentWidth == width) {
                // Setting updated window title
                switch (currentLanguage) {
                case LNG_ENGLISH:
                    app.window.updateTitle("You been rickrolled!");
                    break;

                case LNG_RUSSIAN:
                    app.window.updateTitle("Ты зарикролен!");
                    break;

                case LNG_GERMAN:
                    app.window.updateTitle("Schach на SDL");
                    break;

                case LNG_BELARUSIAN:
                    app.window.updateTitle("Шахматы на SDL");
                    break;
                }
                // Correcting music volume
                //app.music.setVolume();

                // Setting new music and volume back
                //app.music.start(MUS_SINGLEPLAYER);
            }
            // Correcting height
            currentHeight = height * currentWidth / width;
            // Correcting music volume
            //app.music.setVolume();
            //Mix_VolumeMusic(data.musicVolume * currentWidth/currentWidth * currentWidth/currentWidth);

            // Setting timer to update
            prevFrameUpdate = getTime() + (width - currentWidth)*5;
        } else {
            // Updating frame counter
            //frame = (frame + 1) % data.animations[type]->count;
            //prevFrameUpdate = getTime() + data.animations[type]->delays[frame]/3;
        }
    }
    // Updating settings
    settings.update(_app);
}

void SinglePlayerGameCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Drawing buttons
    exitButton.blit(_app.window);

    // Getting pixels of current frame
    /*const Uint8* frameData = (Uint8*)data.animations[type]->frames[frame][0].pixels;
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
            
            _app.window.drawRect(dest);

            // Checkig, if need to make free cell
            if (currentWidth == width || (rand() % width < currentWidth)) {
                SDL_Texture* curTexture = _app.window.getTexture(IMG_names(IMG_GAME_BLACK_PAWN + rand() % 6));

                Uint16 caret = (x + y * width) * 4;

                SDL_SetTextureColorMod(curTexture, frameData[caret+2], frameData[caret+1], frameData[caret]);

                _app.window.blit(curTexture, dest);
            }
        }
    }*/
    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
