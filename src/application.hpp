#pragma once

#include "include.hpp"

class App
{
public:
    SDL_Renderer *renderer;
    SDL_Window *window;
public:
    App();
    ~App();
    inline void setColor(SDL_Color color);
    inline void render();
};
