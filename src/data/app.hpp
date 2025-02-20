/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "libraries.hpp"
#include "music.hpp"
#include "sounds.hpp"
#include "window.hpp"

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

    void run();
public:
    App(/* args */);
    ~App();

    const Window window;
    const Music music;
    const Sounds sounds;
};

extern App app;
