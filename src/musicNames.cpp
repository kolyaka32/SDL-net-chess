/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "musicNames.hpp"

#if (PRELOAD_MUSIC)

// File names of the corresponding music
const char* musicFilesNames[unsigned(Music::Count)] = {
    "mus/menu.mp3",
    "mus/main.mp3",
    "mus/singlePlayer.mp3",
};

#endif  // (PRELOAD_MUSIC)
