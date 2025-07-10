/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "indexesArray.hpp"


template <unsigned length>
IndexesArray<length>::IndexesArray() {
    // Resetting array
    memset(array, 0, length);
    lastPosition = 0;
}

template <unsigned length>
IndexesArray<length>::~IndexesArray() {}

template <unsigned length>
bool IndexesArray<length>::isUnique(Uint8 _index) {
    // Check, if index in array
    for (int i=0; i < length; ++i) {
        if (array[i] == _index) {
            #if CHECK_ALL
            SDL_Log("Index: %u was already get", _index);
            #endif
            return false;
        }
    }
    return true;
}

template <unsigned length>
void IndexesArray<length>::add(Uint8 index) {
    // Adding new index to array, replacing older
    array[lastPosition] = index;
    // Changing caret postion to next
    lastPosition = (lastPosition + 1) % length;
}
