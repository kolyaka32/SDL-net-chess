/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "textures.hpp"
#include "fonts.hpp"
#include "animations.hpp"


// Class of window, where all happen
class Window {
 private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    const Textures textures;
    const Fonts fonts;
    const Animations animations;

 public:
    Window(const DataLoader& loader);
    ~Window() noexcept;

    // Functions for work with graphics
    // Set current draw color
    void setDrawColor(SDL_Color color = {0, 0, 0, 0}) const;
    // Clear all stage with setted color
    void clear() const;
    // Render all buffered objects to screen
    void render() const;

    // Draw simple geometric figures
    void drawPoint(float x, float y) const;
    void drawRect(const SDL_FRect& rect) const;

    // Work with loaded data
    SDL_Texture* getTexture(IMG_names name) const;
    IMG_Animation* getAnimation(ANI_names name) const;

    // Work with own textures
    SDL_Surface* createSurface(int width, int height, SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA32) const;
    SDL_Texture* createTexture(int width, int height, SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET, SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA32) const;
    SDL_Texture* createTexture(SDL_Surface* surface, bool isFree = true) const;
    void blit(SDL_Texture* texture, const SDL_FRect& dest, const SDL_FRect* src = nullptr) const;
    void blit(SDL_Texture* texture, float angle, const SDL_FRect& rect, const SDL_FRect* src = nullptr, SDL_FPoint center = {0, 0}) const;
    void blit(IMG_names name, const SDL_FRect& dest, const SDL_FRect* src = nullptr) const;
    void setRenderTarget(SDL_Texture* target) const;
    void resetRenderTarget() const;
    void setBlendMode(SDL_Texture* _texture, SDL_BlendMode _blendMode = SDL_BLENDMODE_NONE) const;
    void unlockTexture(SDL_Texture* texture) const;
    void destroyTexture(SDL_Texture* texture) const;

    // Work with fonts and text
    TTF_Font* getFont(FNT_names name) const;
    TTF_Font* createFontCopy(FNT_names name, float height) const;
    SDL_Texture* createTexture(FNT_names font, float height, const char* text, unsigned length, SDL_Color color) const;

    // Work with window
    void startTextInput() const;
    void stopTextInput() const;
    void updateTitle() const;
    void updateTitle(const char* name) const;
};
