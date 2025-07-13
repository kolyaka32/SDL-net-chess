/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "libraries.hpp"
#include "preloaded/music.hpp"
#include "preloaded/sounds.hpp"
#include "initFile.hpp"
#include "window.hpp"
#include "languages.hpp"


// Load needed loader, depend on teting
#if ARCHIEVE_LOADING
#include "preloaded/loader/archieveLoader.hpp"
#else
#include "preloaded/loader/straightLoader.hpp"
#endif


// Class of whole current application
class App : Libraries {
private:
    // Selecting loader for data, depend on testing
    #if ARCHIEVE_LOADING
    const ArchieveLoader loader;
    #else
    const StraightLoader loader;
    #endif

    // Flags of work
    static bool running;

public:
    App();

    // Commands to operate with global running
    static void stop();
    static bool isRunning();

    Music music;
    Sounds sounds;
    InitFile initFile;
    const Window window;
};
