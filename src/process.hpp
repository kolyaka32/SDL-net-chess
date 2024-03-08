#pragma once

#include "initFile.hpp"
#include "application.hpp"
#include "graphics.hpp"
#include "icone.hpp"
#include "font.hpp"
#include "audio/sounds.hpp"
#include "audio/musics.hpp"
#include "texts.hpp"


// Structure with all process data
class Data : public Textures, public Icone, public Sounds, public Musics, public Texts
{
private:
    // Extra data
public:
    Data(){
        // Closing data loader after loading all
        closeLoader();
    };
    ~Data(){};
};


// Main process
class Process : public Data
{
public:
    // Extra data
public:
    Process();  // Initialasing all libraries
    int run();
    ~Process();  // Closing all libraries
};

extern Process process;