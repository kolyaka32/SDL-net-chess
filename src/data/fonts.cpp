/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "fonts.hpp"

Fonts::Fonts(const DataLoader& _loader, unsigned _count, const char* _filesNames[]) {
    // Resetting fonts array
    #if CHECK_CORRECTION
    for (unsigned i=0; i < _count; ++i) {
        fonts[i] = nullptr;
    }
    #endif

    // Loading all needed fonts
    for (unsigned i=0; i < _count; ++i) {
        loadFont(_loader, i, _filesNames[i]);
    }

    // Checking massive on loading correction
    #if CHECK_CORRECTION
    for (unsigned i=0; i < FNT_count; ++i) {
        if (fonts[i] == NULL) {
            throw DataLoadException("Fonts at index: " + std::to_string(i));
        }
    }
    #endif
}

Fonts::~Fonts() {
    // Closing all used fonts
    for (unsigned i=0; i < FNT_count; ++i) {
        TTF_CloseFont(fonts[i]);
    }
}

void Fonts::loadFont(const DataLoader& _loader, unsigned _index, const char* _name) {
    SDL_IOStream* iodata = _loader.load(_name);

    fonts[_index] = TTF_OpenFontIO(iodata, true, 20.);

    // Checking correction of loaded font
    #if CHECK_CORRECTION
    if (fonts[_index] == nullptr) {
        throw DataLoadException(_name);
    }
    #endif
}

TTF_Font* Fonts::operator[](FNT_names _index) const {
    return fonts[_index];
}
