/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"

// Additional logging to file system
#if (CHECK_ALL)
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_iostream.h>
#endif


// Object for correct logging of main actions
class Logger {
 protected:
    #if (CHECK_ALL)
    SDL_IOStream* logFile = nullptr;
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
    // Writing to stdout
    SDL_Log(_text, _args...);
    // Writing to file
    SDL_IOprintf(logFile, _text, _args...);
    SDL_IOprintf(logFile, "\n");
    SDL_FlushIO(logFile);
    #endif
}

template <typename ...Args>
void Logger::additional(const char* _text, const Args& ..._args) {
    #if (CHECK_CORRECTION)
    // Writing to stdout
    SDL_Log(_text, _args...);
    // Writing to file
    SDL_IOprintf(logFile, _text, _args...);
    SDL_IOprintf(logFile, "\n");
    SDL_FlushIO(logFile);
    #endif
}
