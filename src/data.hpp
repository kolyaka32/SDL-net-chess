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
private:
    // Extra data
public:
    bool running;  // Global process run flag
    Data(){
        // Closing data loader after loading all
        closeLoader();
    };
    ~Data(){};
};

extern Data data;
