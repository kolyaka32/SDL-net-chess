#pragma once

#include "initFile.hpp"
#include "application.hpp"
#include "graphics.hpp"
#include "font.hpp"
#include "sounds.hpp"
#include "musics.hpp"
#include "texts.hpp"

// Main process
class Process : public InitFile, App, Graphics, Font, Sounds, Musics, Texts
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
    Process(/* args */);  // Initialasing all libraries
    int run();
    ~Process();  // Closing all libraries
};

extern Process process;