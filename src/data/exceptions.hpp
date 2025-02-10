/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <stdexcept>
#include <SDL3/SDL_log.h>
#include "../testing.hpp"

// Custom exceptions
#if CHECK_CORRECTION
// Any error of loading
class LoadException : public std::exception {
protected:
    const char* message;
public:
    LoadException() : message("Unknown error\n") {};
    LoadException(const std::string _message) : message(_message.std::string::c_str()) {};
    ~LoadException() {};
    const char* what() const noexcept override {
        SDL_Log(message);
        return message;
    };
};

// Error of loading library
class LibararyLoadException : LoadException {
public:
    LibararyLoadException(const std::string _library = "")
        : LoadException("Error with loading library: " + _library + '\n') {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, message);
    };
    const char* what() const noexcept override {
        SDL_LogCritical(SDL_LOG_PRIORITY_CRITICAL, message);
        return message;
    };
};

// Error with loading data
class DataLoadException : LoadException {
public:
    DataLoadException(const std::string _dataType = "")
        : LoadException("Error with load file: " + _dataType + '\n') {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, message);
    };
    const char* what() const noexcept override {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, message);
        return message;
    };
};
#endif
