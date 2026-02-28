/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_timer.h>
#include "logger.hpp"


// Macros for better getting time
#define getTime SDL_GetTicks

// Type of data for storing time
typedef unsigned long long timer;
