/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "straightLoader.hpp"

StraightLoader::StraightLoader() {}

StraightLoader::~StraightLoader() {}

SDL_IOStream* StraightLoader::load(const char* _fileName) const {
    // Creating modified name
    char* fileName = new char[strlen(_fileName) + strlen("../") + 1];
    strcpy(fileName, "../");
    strcat(fileName, _fileName);

    // Openning file straight from system
    SDL_IOStream* data = SDL_IOFromFile(fileName, "r");

    // Clearing temporary name
    delete[] fileName;

    // Checking correction of loaded font
    #if CHECK_CORRECTION
    if (data == nullptr) {
        throw DataLoadException(_fileName);
    }
    #endif

    return data;
}