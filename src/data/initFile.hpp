/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>

#include "../include.hpp"
#include "languages.hpp"

// Class of object to save user options
class InitFile {
 public:
    language language;        // Game language for all texts
    unsigned musicVolume;     // Start volume of music
    unsigned soundsVolume;    // Start volume of effects
    unsigned drawFPS;         // Setted frames per seconds
    std::string baseIP;       // Saved ip for better expirience
    std::string basePort;     // Saved connection port for better expirience
    std::string startConfig;  // Start field configuration
 public:
    InitFile();   // Load all settings from init file
    ~InitFile();  // Save all settings to init file
};
