/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "libraries.hpp"
#include "music.hpp"
#include "sounds.hpp"
#include "initFile.hpp"
#include "window.hpp"
#include "../cycles/cycles.hpp"

// Load needed loader, depend on teting
#if ARCHIEVE_LOADING
#include "loader/archieveLoader.hpp"
#else
#include "loader/straightLoader.hpp"
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
    bool running = true;
    CYCLE_types nextCycle = CYCLE_MENU;

public:
    App();
    ~App();

    // Commands to operate with global running
    void stop();
    void startNextCycle(CYCLE_types type);
    
    // Command to start cycles
    void run();

    Music music;
    Sounds sounds;
    InitFile initFile;
    const Window window;
};
