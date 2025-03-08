/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"
#include "../data/window.hpp"

// Class with letters, placed in collumn
class LettersCollumn {
 private:
    TTF_Font* font = nullptr;  // Font for draw any letters

 public:
    LettersCollumn(const Window& target, char startLetter, Uint8 length, Sint8 xOffset, Sint8 yOffset);
    ~LettersCollumn();

    SDL_Texture* texture;
};


// Class of drawing board frame with letters for better UI
class SurroundingLetters {
 private:
    const LettersCollumn numberCollumn;  // Vertical column with numbers
    const LettersCollumn letterCollumn;  // Horizontal column with letters

 public:
    SurroundingLetters(const Window& target);
    void blit(const Window& target) const;
};
