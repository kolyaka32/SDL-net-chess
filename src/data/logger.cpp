/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include <SDL3/SDL.h>
#include "logger.hpp"


Logger::Logger()
#if (CHECK_ALL)
{
    // File name
    char fileName[20];
    // Index of name
    int i = 0;

    // Finding avaliable file name
    while (logFile == nullptr) {
        // Creating file name
        SDL_snprintf(fileName, sizeof(fileName), LOG_NAME, i);
        // Updating index
        i++;

        // Trying open file, blocking by app
        logFile = SDL_IOFromFile(fileName, "w");
    }
    additional("Started logging to: %s", fileName);
}
#else
{}
#endif

Logger::~Logger() noexcept {
    #if (CHECK_ALL)
    additional("Finished correctly");
    SDL_CloseIO(logFile);
    #endif
}
