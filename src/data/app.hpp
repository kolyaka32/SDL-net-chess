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
    static bool restarting;

public:
    App();

    // Commands to operate with global running
    static void stop();
    static bool isRunning();
    static void restart();
    static void resetRestart();
    static bool isRestarted();

    // Templated function for run new cycle
    template <class T>
    void runCycle();

    Music music;
    Sounds sounds;
    InitFile initFile;
    const Window window;
};


template <class T>
void App::runCycle() {
    // Resetting
    restarting = false;

    // Running current cycle, while restarting
    do {
        // Updating location
        App::window.updateTitle();
        // Launching new cycle
        T cycle(*this);
        cycle.run(*this);
    } while (restarting && running);
}
