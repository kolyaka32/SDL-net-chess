/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "logger.hpp"


Logger::Logger()
#if (CHECK_ALL)
: logFile(LOG_NAME) {
    // Setting to write without buffering for correct work with errors
    logFile << std::unitbuf;

    additional("Started logging with file name: %s", LOG_NAME);
}
#else
{}
#endif

Logger::~Logger() noexcept {
    #if (CHECK_ALL)
    logFile.close();
    #endif
}
