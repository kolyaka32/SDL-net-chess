/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "music.hpp"
#include "sounds.hpp"
#include "window.hpp"

#if ARCHIEVE_LOADING
#include "loader/archieveLoader.hpp"
#else
#include "loader/straightLoader.hpp"
#endif

class App {
private:
    // Selecting loader for data, depend on state of testing
    #if ARCHIEVE_LOADING
    const ArchieveLoader loader;
    #else
    const StraightLoader loader;
    #endif

    void run();
public:
    App(/* args */);
    ~App();

    Window window;
    const Music music;
    const Sounds sounds;
};

extern App app;
