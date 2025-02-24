/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "letters.hpp"


// Class with letters, placed in collumn
LettersCollumn::LettersCollumn(const Window& _target, char _startLetter, Uint8 _length, Sint8 _xOffset, Sint8 _yOffset) {
    // Creating font
    font = _target.getFont(FNT_MAIN);
    TTF_SetFontSize(font, 20);

    // Creating main texture
    SDL_Surface* tempSurface = _target.createSurface(_xOffset ? _length * CELL_SIDE : LETTER_LINE, _yOffset ? _length * CELL_SIDE : LETTER_LINE);

    // Creating texture draw place
    SDL_Rect dest;

    // Creating collumn of letters
    for (Uint8 i=0; i < _length; ++i) {
        // Creating surface with need letter
        SDL_Surface* letterSurface = TTF_RenderGlyph_Shaded(font, _startLetter + i, WHITE, BLACK);

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
        SDL_DestroySurface(letterSurface);
    }
    // Creating texture
    texture = _target.createTexture(tempSurface);

    SDL_DestroySurface(tempSurface);
}

// Savely clear all rest data
LettersCollumn::~LettersCollumn() {
    // Clearing texture
    SDL_DestroyTexture(texture);
}



// Class of drawing board frame with letters for better UI
SurroundingLetters::SurroundingLetters(const Window& _target)
: numberCollumn{_target, '1', 8, 0, -CELL_SIDE},
letterCollumn{_target, 'A', 8, CELL_SIDE, 0} {}

void SurroundingLetters::blit(const Window& _target) const {
    // Drawing numbers
    // Left collumn
    _target.blit(numberCollumn.texture, {0, UPPER_LINE - LETTER_LINE/2 + CELL_SIDE/2, LETTER_LINE, GAME_HEIGHT});
    // Right column
    _target.blit(numberCollumn.texture, {SCREEN_WIDTH-RIGHT_LINE, UPPER_LINE - LETTER_LINE/2 + CELL_SIDE/2, LETTER_LINE, GAME_HEIGHT});

    // Drawing letters
    // Upper collumn
    _target.blit(letterCollumn.texture, {LEFT_LINE/2 + CELL_SIDE/2, UPPER_LINE - LETTER_LINE, GAME_WIDTH, LETTER_LINE});
    // Bottom column
    _target.blit(letterCollumn.texture, {LEFT_LINE/2 + CELL_SIDE/2, SCREEN_HEIGHT - LETTER_LINE, GAME_WIDTH, LETTER_LINE});
}
