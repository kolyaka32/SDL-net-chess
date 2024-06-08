/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "initFile.hpp"
#include "graphics.hpp"
#include "icone.hpp"
#include "font.hpp"
#include "audio/sounds.hpp"
#include "audio/musics.hpp"
#include "texts.hpp"


// Structure with all process data
class Data :
public Textures, public Icone, public Font,
public Sounds, public Musics, public Animations, public Texts {
 public:
    bool appRunning = true;   // Global process run flag
    bool restart = false;  // Global flag of restart current process
    // Initialasing process data
    Data(){
        // Closing data loader after loading all
        closeLoader();
    }
};

// Global structure with all process data
extern Data data;
