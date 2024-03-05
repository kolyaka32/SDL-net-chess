#pragma once

#include "initFile.hpp"
#include "application.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "audio/sounds.hpp"
#include "audio/musics.hpp"
#include "texts.hpp"


// Main process
class Process : public Textures, public Sounds, public Musics, public Texts
{
public:
    // Extra data
public:
    Process();  // Initialasing all libraries
    int run();
    ~Process();  // Closing all libraries
};

extern Process process;