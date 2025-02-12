/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#if ARCHIEVE_LOADING
#include "loader/straightLoader.hpp"
#else
#include "loader/archieveLoader.hpp"
#endif

#include "music.hpp"
#include "sounds.hpp"
#include "window.hpp"


class App {
private:
    // Selecting loader for data, depend on state of testing
    #if ARCHIEVE_LOADING
    const StraightLoader loader;
    #else
    const ArchieveLoader loader;
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
