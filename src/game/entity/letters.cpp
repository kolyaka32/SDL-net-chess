/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "letters.hpp"

#include "../../data/data.hpp"


// Class with letters, placed in collumn
LettersCollumn::LettersCollumn(const char _startLetter, const Uint8 _length, Sint8 _xOffset, Sint8 _yOffset) {
    // Creating font (if need)
    if (!font) {
        font = data.createFont(20);
    }

    // Creating main texture
    SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, _xOffset ? _length * CELL_SIDE : LETTER_LINE,
        _yOffset ? _length * CELL_SIDE : LETTER_LINE, 32, 0, 0, 0, 0);

    // Creating texture draw place
    SDL_Rect dest;

    // Creating collumn of letters
    for (Uint8 i=0; i < _length; ++i) {
        // Creating surface with need letter
        const char text[2] = {(char)(_startLetter + i), '\0'};  // Text for surface
        SDL_Surface* letterSurface = TTF_RenderUTF8_Shaded(font, text, WHITE, BLACK);

        // Updating texture parametrs
        dest.x = 5 + i * _xOffset;
        dest.y = -5 + i * _yOffset;

        // Check, if draw form other side
        if (_xOffset < 0) {
            dest.x += CELL_SIDE*(_length-1);
        }
        if (_yOffset < 0) {
            dest.y += CELL_SIDE*(_length-1);
        }

        // Copying surface to main
        SDL_BlitSurface(letterSurface, nullptr, tempSurface, &dest);

        // Freeing temp data
        SDL_FreeSurface(letterSurface);
    }
    // Creating texture
    texture = SDL_CreateTextureFromSurface(data.renderer, tempSurface);

    SDL_FreeSurface(tempSurface);
}

// Savely clear all rest data
LettersCollumn::~LettersCollumn() {
    // Clearing texture
    SDL_DestroyTexture(texture);
}



// Class of drawing board frame with letters for better UI
SurroundingLetters::SurroundingLetters() {}

SurroundingLetters::~SurroundingLetters() {}

void SurroundingLetters::blit() const {
    const static SDL_Rect column1 = {0, UPPER_LINE - LETTER_LINE/2 + CELL_SIDE/2, LETTER_LINE, GAME_HEIGHT};
    const static SDL_Rect column2 = {SCREEN_WIDTH-RIGHT_LINE, UPPER_LINE - LETTER_LINE/2 + CELL_SIDE/2, LETTER_LINE, GAME_HEIGHT};
    const static SDL_Rect column3 = {LEFT_LINE/2 + CELL_SIDE/2, UPPER_LINE - LETTER_LINE, GAME_WIDTH, LETTER_LINE};
    const static SDL_Rect column4 = {LEFT_LINE/2 + CELL_SIDE/2, SCREEN_HEIGHT - LETTER_LINE, GAME_WIDTH, LETTER_LINE};

    // Drawing numbers
    // Left collumn
    SDL_RenderCopy(data.renderer, numberCollumn.texture, nullptr, &column1);
    // Right column
    SDL_RenderCopy(data.renderer, numberCollumn.texture, nullptr, &column2);

    // Drawing letters
    // Upper collumn
    SDL_RenderCopy(data.renderer, letterCollumn.texture, nullptr, &column3);
    // Bottom column
    SDL_RenderCopy(data.renderer, letterCollumn.texture, nullptr, &column4);
}
