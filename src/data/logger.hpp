/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_log.h>
#include "../define.hpp"


// Additional logging to file system
#if (CHECK_ALL)
#include <fstream>
extern std::ofstream logFile;
#endif

// Function for log important information
template <typename ...Args>
void logImportant(const char* text, const Args& ...args) {
    #if (CHECK_CORRECTION)
    // Writing to stdout
    SDL_Log(text, args...);
    // Writing to file
    char buffer[100];
    snprintf(buffer, sizeof(buffer), text, args...);
    logFile << buffer << '\n';
    #endif
}

// Function for log additional information
template <typename ...Args>
void logAdditional(const char* text, const Args& ...args) {
    #if (CHECK_ALL)
    // Writing to stdout
    SDL_Log(text, args...);
    // Writing to file
    char buffer[100];
    snprintf(buffer, sizeof(buffer), text, args...);
    logFile << buffer << '\n';
    #endif
}
