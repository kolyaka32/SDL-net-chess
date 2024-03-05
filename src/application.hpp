#pragma once

#include "include.hpp"
#include "initFile.hpp"


class App : public InitFile
{
public:
    SDL_Renderer *renderer;
    SDL_Window *window;
public:
    App();
    ~App();
    void setColor(SDL_Color color);
    void render();
};
