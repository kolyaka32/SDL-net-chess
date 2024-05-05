#pragma once

#include <mutex>

#include "../include.hpp"
#include "initFile.hpp"


// Class with main renderer and window object
class App : public virtual InitFile
{
public:
    SDL_Renderer *renderer;  // Renderer for draw any objects at screen
    SDL_Window *window;      // Main window, where objects draw to
    std::mutex drawMutex;    // Mutex for bloack any activity, while render
public:
    App();   // Creating renderer and window
    ~App();  // Close renderer and window
    void setColor(SDL_Color color);  // Setting color for draw
    void render();                   // Blitting all buffered objects
    void waitInternet();             // Waiting next cycle for load decrease
    void waitDraw();                 // Waiting next cycle for load decrease
};
