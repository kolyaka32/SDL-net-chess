/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "singlePlayer.hpp"
#include "selectCycle.hpp"


SinglePlayerGameCycle::SinglePlayerGameCycle(App& _app)
: BaseCycle(_app),
app(_app),
startVolume(_app.music.getVolume()),
animation(_app.window.getAnimation(ANI_SINGLEPLAYER)),
width(animation->w),
height(animation->h) {
    prevFrameUpdate = getTime() + 400;

    // Starting main song (if wasn't started)
    if(!isRestarted()) {
        _app.music.start(MUS_MAIN);
    }
}

SinglePlayerGameCycle::~SinglePlayerGameCycle() {
    // Resetting title
    app.window.updateTitle();

    // Resetting volume
    app.music.setVolume(startVolume);

    // Resetting color for figures
    for (unsigned i = IMG_GAME_WHITE_PAWN; i <= IMG_GAME_BLACK_KING; ++i) {
        app.window.setColorMode(IMG_names(i));
    }
}

void SinglePlayerGameCycle::inputMouseDown(App& _app) {
    // Clicking in settings menu
    if (settings.click(mouse)) {
        return;
    }
    // Exiting to menu
    if (exitButton.in(mouse)) {
        stop();
        return;
    }
    // Changing volume
    if (currentWidth != width) {
        startVolume = _app.music.getVolume();
        app.music.setVolume(startVolume * (width-currentWidth)/width);
    }
}

void SinglePlayerGameCycle::update(App& _app) {
    BaseCycle::update(_app);

    // Checking, if need to change state
    if (getTime() > prevFrameUpdate) {
        // Changing length until reach need width
        if (currentWidth < width) {
            // Increasing field width
            currentWidth++;

            // Waiting for full width
            if (currentWidth == width) {
                // Setting updated window title
                switch (LanguagedText::getLanguage()) {
                case Language::English:
                    app.window.updateTitle("You been rickrolled!");
                    break;

                case Language::Russian:
                    app.window.updateTitle("Ты зарикролен!");
                    break;

                case Language::German:
                    app.window.updateTitle("Schach на SDL");
                    break;

                case Language::Bellarusian:
                    app.window.updateTitle("Шахматы на SDL");
                    break;
                }
                // Setting new music and volume back
                _app.music.setVolume(startVolume*2);
                _app.music.start(MUS_SINGLEPLAYER);
                return;
            }
            // Correcting height
            currentHeight = height * currentWidth / width;
            // Correcting music volume
            app.music.setVolume(startVolume * (width-currentWidth)/width);

            // Setting timer to update
            prevFrameUpdate = getTime() + (width - currentWidth)*5;
        } else {
            // Updating frame counter
            frame = (frame + 1) % animation->count;
            prevFrameUpdate = getTime() + animation->delays[frame]/3;
        }
    }
}

void SinglePlayerGameCycle::draw(const App& _app) const {
    // Bliting background
    _app.window.setDrawColor(BLACK);
    _app.window.clear();

    // Drawing buttons
    exitButton.blit(_app.window);

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
                _app.window.setDrawColor(FIELD_LIGHT);
            } else {
                _app.window.setDrawColor(FIELD_DARK);
            }
            
            _app.window.drawRect(dest);

            // Checkig, if need to make free cell
            if (currentWidth == width || (rand() % width < currentWidth)) {
                SDL_Texture* curTexture = _app.window.getTexture(IMG_names(IMG_GAME_BLACK_PAWN + rand() % 6));

                Uint16 caret = (x + y * width) * 4;

                _app.window.setColorMode(curTexture, {frameData[caret+2], frameData[caret+1], frameData[caret]});

                _app.window.blit(curTexture, dest);
            }
        }
    }
    // Drawing settings
    settings.blit(_app.window);

    // Bliting all to screen
    _app.window.render();
}
