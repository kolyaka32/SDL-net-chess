#pragma once

#include "initFile.hpp"
#include "graphics.hpp"
#include "icone.hpp"
#include "font.hpp"
#include "audio/sounds.hpp"
#include "audio/musics.hpp"


// Structure with all process data
class Data : public virtual Textures, public virtual Icone, public virtual Font, public virtual Sounds, public virtual Musics
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

extern Data data;
