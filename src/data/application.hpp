/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../include.hpp"
#include "initFile.hpp"


// Class with main renderer and window object
class App : public virtual InitFile {
 public:
    SDL_Renderer *renderer;          // Renderer for draw any objects at screen
    SDL_Window *window;              // Main window, where objects draw to
 public:
    App();                           // Creating renderer and window
    ~App();                          // Close renderer and window
    void setColor(SDL_Color color);  // Setting color for draw
    void render();                   // Blitting all buffered objects
};
