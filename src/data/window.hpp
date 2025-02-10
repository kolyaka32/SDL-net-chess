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
    ~Window() noexcept;

    // Functions for work with graphics
    // Set current draw color
    void setDrawColor(SDL_Color color = {0, 0, 0, 0});
    // Clear all stage with setted color
    void clear();
    // Render all buffered objects to screen
    void render();

    // Draw simple geometric figures
    void drawPoint(float x, float y);
    void drawRect(const SDL_FRect& rect);

    // Work with loaded textures
    SDL_Texture* getTexture(IMG_names name);

    // Work with own textures
    SDL_Texture* createTexture(int width, int height, SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET, SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA32);
    SDL_Texture* createTexture(SDL_Surface* surface, bool isFree = true);
    void blit(SDL_Texture* texture, const SDL_FRect* dest, const SDL_FRect* src = nullptr);
    void blit(SDL_Texture* texture, float angle, const SDL_FRect* rect, const SDL_FRect* src = nullptr, SDL_FPoint center = {0, 0});
    void setRenderTarget(SDL_Texture* target);
    void resetRenderTarget();
    void setBlendMode(SDL_Texture* _texture, SDL_BlendMode _blendMode = SDL_BLENDMODE_NONE);
    void unlockTexture(SDL_Texture* texture);
    void destroyTexture(SDL_Texture* texture);

    // Work with fonts
    void blitText(const char* text, const SDL_FRect& rect);
};
