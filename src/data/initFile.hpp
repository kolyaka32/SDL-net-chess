#pragma once

#include <string>
#include "../include.hpp"


// Class of object to save user options
class InitFile {
 public:
    Uint8 language;           // Game language for all texts
    Uint8 musicVolume;        // Start volume of music
    Uint8 soundsVolume;       // Start volume of effects
    Uint16 drawFPS;           // Setted frames per seconds
    std::string baseIP;       // Saved ip for better expirience
    std::string basePort;     // Saved connection port for better expirience
    std::string startConfig;  // Start field configuration
 public:
    InitFile();   // Load all settings from init file
    ~InitFile();  // Save all settings to init file
};
