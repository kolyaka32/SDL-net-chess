/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "logger.hpp"
#include "libraries.hpp"
#include "preloaded/loader/loader.hpp"
#include "preloaded/audio.hpp"
#include "../internet/internet.hpp"
#include "initFile.hpp"


// Initialasing global objects in correct order
// Logger
#if (CHECK_ALL)
std::ofstream logFile{LOG_NAME};
#endif

// All side libries
Libraries libraries{};

#if (PRELOAD_DATA)
const DataLoader dataLoader{};
#endif

#if (USE_SDL_MIXER)
Audio audio{};
#endif

#if (USE_NET)
Internet internet{};
#endif

// Loading/unloading all parameters for game
#if (USE_SETTING_FILE)
InitFile initFile{};
#endif
