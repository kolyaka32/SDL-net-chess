/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "textures.hpp"
#include "fonts.hpp"


// Class of window, where all happen
class Window
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Textures textures;
    const Fonts fonts;
public:
    Window(const DataLoader& loader);
    ~Window();

    // Functions for work with graphics
    // Set current draw color
    void setDrawColor(SDL_Color color = {0, 0, 0, 0});
    // Clear all stage with setted color
    void clear();
    // Render all buffered objects to screen
    void render();

    // Draw simple geometric figures
    void drawPoint(int x, int y);
    void drawRect(const SDL_Rect& rect);

    // Blitting images
    void blit(IMG_names name, const SDL_Rect* dest, const SDL_Rect* src = nullptr);
    void blit(IMG_names name, float angle, const SDL_Rect* rect, const SDL_Rect* src = nullptr, SDL_Point center = {0, 0});
    void queryTexture(IMG_names name, int* width, int* height);

    // Work with own textures
    SDL_Texture* createTexture(int width, int height, SDL_PixelFormatEnum format = SDL_PIXELFORMAT_RGB888);
    void blit(SDL_Texture* texture, const SDL_Rect* dest, const SDL_Rect* src = nullptr);
    void setRenderTarget(SDL_Texture* target = nullptr);
    void setBlendMode(SDL_Texture* _texture, SDL_BlendMode _blendMode = SDL_BLENDMODE_NONE);
    void unlockTexture(SDL_Texture* texture);
    void destroyTexture(SDL_Texture* texture);

    // Work with fonts
    void blitText(const char* text, const SDL_Rect& rect);
};
