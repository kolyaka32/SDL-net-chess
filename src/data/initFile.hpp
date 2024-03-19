#pragma once

#include <string>
#include "../include.hpp"

//
class InitFile
{
public:
    Uint8 language;
    Uint8 MusicVolume;  // Start volume of music
    Uint8 EffectsVolume;  // Start volume of effects
    Uint16 drawFPS;  // Setted frames per seconds
    std::string baseIP;    // Saved ip for better expirience
    std::string basePort;  // Saved connection port for better expirience
    std::string startConfig;  // Start field configuration
public:
    InitFile();
    ~InitFile();
};
