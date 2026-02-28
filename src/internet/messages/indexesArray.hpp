/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <array>
#include <SDL3/SDL_stdinc.h>


// Class for work with indexes of last get message
template <unsigned length>
class IndexesArray {
 private:
    // Array with last getted messages for check repeats
    std::array<Uint8, length> array;
    // Position in array with last get message (for correct updation)
    int lastPosition;

 public:
    IndexesArray();
    bool isUnique(Uint8 index);
    void add(Uint8 index);
};
