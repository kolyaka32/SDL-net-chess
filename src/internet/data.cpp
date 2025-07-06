/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "data.hpp"

Uint8 swapLE(Uint8 object) {
    return object;
}

Sint8 swapLE(Sint8 object) {
    return object;
}

Uint16 swapLE(Uint16 object) {
    return SDL_Swap16LE(object);
}

Sint16 swapLE(Sint16 object) {
    return SDL_Swap16LE(object);
}

Uint32 swapLE(Uint32 object) {
    return SDL_Swap32LE(object);
}

Sint32 swapLE(Sint32 object) {
    return SDL_Swap32LE(object);
}

float swapLE(float object) {
    return SDL_SwapFloatLE(object);
}

Uint64 swapLE(Uint64 object) {
    return SDL_Swap64LE(object);
}

Sint64 swapLE(Sint64 object) {
    return SDL_Swap64LE(object);
}

// Templated function for rest of objects (unsecure)
template <typename T>
T swapLE(T object) {
    #if CHECK_CORRECTION
    throw "You not suppose to do use that value format";
    #endif
    return object;
}

template <typename T>
Uint8* writeData(Uint8* array, T object) {
    *(array) = swapLE<T>(object);
    return array+sizeof(object);
}

template <typename T>
T getData(Uint8* array) {
    return swapLE<T>((T)array);
}
