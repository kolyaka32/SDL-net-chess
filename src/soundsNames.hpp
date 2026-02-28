/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "define.hpp"

#if (PRELOAD_SOUNDS)

// Names of sound effects
enum class Sounds {
    // Game part
    Turn,
    Reset,

    // Global counter of all loaded sounds
    Count,

    // Shortcut for changing slider sound in settings
    SliderSound = Turn,
};

// File names of the corresponding sounds
extern const char* soundsFilesNames[unsigned(Sounds::Count)];

#endif  // (PRELOAD_SOUNDS)
