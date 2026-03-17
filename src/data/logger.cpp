/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "logger.hpp"


Logger::Logger()
: logFile(LOG_NAME) {
    #if (CHECK_ALL)
    // Setting to write without buffering for correct work with errors
    logFile << std::unitbuf;

    additional("Started logging with file name: %s", LOG_NAME);
    #endif
}

Logger::~Logger() noexcept {
    logFile.close();
}
