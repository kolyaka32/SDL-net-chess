#pragma once

#include "initFile.hpp"
#include "application.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "audio/sounds.hpp"
#include "audio/musics.hpp"
#include "texts.hpp"

// Main process
class Process : public InitFile, public App, public Textures, public Sounds, public Musics, public Texts
{
//public:
    /*InitFile initFile;
    App app;
    Graphics graphics;
    Font font;
    Sounds sounds;
    Musics musics;
    Texts texts;*/
public:
    Process();  // Initialasing all libraries
    int run();
    ~Process();  // Closing all libraries
};

extern Process process;