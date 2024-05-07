#pragma once

#include "../../include.hpp"
#include "../../define.hpp"


// Class with letters, placed in collumn
class LettersCollumn
{
private:
    TTF_Font* font = nullptr;  // Font for draw any letters
public:
    LettersCollumn(const char startLetter, const Uint8 length, Sint8 xOffset, Sint8 yOffset);
    ~LettersCollumn();

    SDL_Texture* texture;
};


// Class of drawing board frame with letters for better UI
class SurroundingLetters
{
private:
    const LettersCollumn numberCollumn{'1', 8, 0, -CELL_SIDE};  // Vertical column with numbers
    const LettersCollumn letterCollumn{'A', 8, CELL_SIDE, 0};  // Horizontal column with letters
public:
    SurroundingLetters();
    ~SurroundingLetters();
    void blit() const;
};
