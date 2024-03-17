#pragma once

#include "initFile.hpp"
#include "graphics.hpp"
#include "icone.hpp"
#include "font.hpp"
#include "audio/sounds.hpp"
#include "audio/musics.hpp"
#include "texts.hpp"


// Structure with all process data
class Data : public virtual Textures, public virtual Icone, public virtual Font, public virtual Sounds, public virtual Musics, public virtual Texts
{
public:
    bool running = true;   // Global process run flag
    bool restart = false;  // Global flag of restart current process
    // Initialasing process data
    Data(){
        // Closing data loader after loading all
        closeLoader();
    };
};

// Global structure with all process data
extern Data data;
