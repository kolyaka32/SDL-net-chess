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
#include "../cycles/cycles.hpp"


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
    bool running = true;
    Cycle nextCycle = Cycle::Menu;

protected:
    // Templated function for run new cycle
    template <class T>
    void runCycle() {
        T cycle(*this);
        cycle.run(*this);
    }

public:
    App();
    ~App();

    // Commands to operate with global running
    void stop();
    void startNextCycle(Cycle type);

    // Command to start cycles
    void run();

    Music music;
    Sounds sounds;
    InitFile initFile;
    const Window window;
};
