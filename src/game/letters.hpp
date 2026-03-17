/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Class with letters, placed in collumn
class LettersCollumn : GUI::TextureTemplate {
 public:
    LettersCollumn(const Window& target, char startLetter, Uint8 length, Sint8 xOffset, Sint8 yOffset);
    ~LettersCollumn();
    void blit(const SDL_FRect dest) const;
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
