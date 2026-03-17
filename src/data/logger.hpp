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
#endif


// Object for correct logging of main actions
class Logger {
 protected:
    #if (CHECK_ALL)
    std::ofstream logFile;
    #endif

 public:
    Logger();
    ~Logger() noexcept;

    // Function for log important information (errors)
    template <typename ...Args>
    void important(const char* text, const Args& ...args);

    // Function for log additional information
    template <typename ...Args>
    void additional(const char* text, const Args& ...args);
};

// Global object for logging
extern Logger logger;


template <typename ...Args>
void Logger::important(const char* _text, const Args& ..._args) {
    #if (CHECK_CORRECTION)
    // Creating text
    char* buffer;
    SDL_asprintf(&buffer, _text, _args...);
    // Writing to stdout
    SDL_Log(buffer);
    // Writing to file
    logFile << buffer << '\n';
    // Clearing text
    SDL_free(buffer);
    #endif
}

template <typename ...Args>
void Logger::additional(const char* _text, const Args& ..._args) {
    #if (CHECK_CORRECTION)
    // Creating text
    char* buffer;
    SDL_asprintf(&buffer, _text, _args...);
    // Writing to stdout
    SDL_Log(buffer);
    // Writing to file
    logFile << buffer << '\n';
    // Clearing text
    SDL_free(buffer);
    #endif
}
