/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "cstring"

#include "../define.hpp"
#include "dataLoader.hpp"
#include "loadExceptions.hpp"


// Loading data from file system (for testing)
#if !ARCHIEVE_LOADING


// Opening archive not needed
DataLoader::DataLoader() {}

// Closing archieve not needed
void DataLoader::closeLoader() {}

// System to load object with need name (from file system)
SDL_RWops *DataLoader::loadObject(const std::string _name) {
    // Openning need file
    SDL_RWops *tempRW = SDL_RWFromFile(("../" + _name).std::string::c_str(), "r");

    // Checking file correction
    #if CHECK_CORRECTION
    if (!tempRW) {
        throw DataLoadException("load file: " + _name);
    }
    #endif

    // Returning created data structure
    return tempRW;
}

#endif

