/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_render.h>
#include "colors.hpp"
#include "time.hpp"
#include "preloaded/textures.hpp"
#include "preloaded/animations.hpp"
#include "preloaded/fonts.hpp"
#include "languages.hpp"


// Class of window, drawn functions, work with it
class Window {
 private:
    int width, height;
    const LanguagedText titleText;
    SDL_Window* window;
    SDL_Renderer* renderer;
    #if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
    // Preloaded textures
    const TexturesData textures;
    #endif
    #if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
    // Preloaded animations
    const AnimationsData animations;
    #endif
    #if (USE_SDL_FONT) && (PRELOAD_FONTS)
    // Preloaded fonts
    const FontsData fonts;
    #endif

    // Set new title
    void updateTitle(const char* name) const;

 public:
    Window(int width, int height, const LanguagedText title);
    ~Window() noexcept;

    // Functions for work with graphics
    // Operate with sizes of window
    int getWidth() const;
    int getHeight() const;
    void setWidth(int width);
    void setHeight(int height);
    // Set current draw color
    void setDrawColor(Color color = EMPTY) const;
    // Clear all stage with setted color
    void clear() const;
    // Render all buffered objects to screen
    void render() const;

    // Draw simple geometric figures
    void drawPoint(float x, float y) const;
    void drawRect(const SDL_FRect& rect) const;
    void drawLine(float x1, float y1, float x2, float y2) const;

    // Work with own surfaces
    SDL_Surface* createSurface(int width, int height, SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA32) const;
    void setBlendMode(SDL_Surface* surface, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE) const;
    void destroy(SDL_Surface* surface) const;

    // Work with own textures
    SDL_Texture* createTexture(int width, int height, SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET,
        SDL_PixelFormat format = SDL_PIXELFORMAT_RGBA32) const;
    SDL_Texture* createTexture(SDL_Surface* surface) const;
    SDL_Texture* createTextureAndFree(SDL_Surface* surface) const;
    void copyTexture(SDL_Texture* dest, SDL_Texture* src) const;
    void blit(SDL_Texture* texture, const SDL_FRect& dest) const;
    void blit(SDL_Texture* texture, const SDL_FRect* dest = nullptr, const SDL_FRect* src = nullptr) const;
    void blit(SDL_Texture* texture, float angle, const SDL_FRect& rect, const SDL_FRect* src = nullptr,
        SDL_FPoint center = {0, 0}) const;
    void setRenderTarget(SDL_Texture* target) const;
    void resetRenderTarget() const;
    void setBlendMode(SDL_Texture* texture, SDL_BlendMode blendMode = SDL_BLENDMODE_NONE) const;
    void setColorMode(SDL_Texture* texture, Color color = EMPTY) const;
    void unlock(SDL_Texture* texture) const;
    void destroy(SDL_Texture* texture) const;

    // Work with preloaded textures
    #if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
    SDL_Texture* getTexture(Textures name) const;
    #endif

    // Work with preloaded animations
    #if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
    IMG_Animation* getAnimation(Animations name) const;
    #endif

    // Work with preloaded fonts and text
    #if (USE_SDL_FONT) && (PRELOAD_FONTS)
    TTF_Font* getFont(Fonts name) const;
    TTF_Font* createFontCopy(Fonts name, float height) const;
    SDL_Texture* createTexture(Fonts font, float height, const char* text, unsigned length, Color color) const;
    SDL_Texture* createTexture(TTF_Font* font, const char* text, Color color) const;
    #endif

    // Draw raw text without TTF library
    template <typename ...Args>
    void drawDebugText(float X, float Y, const char* text, const Args& ...args) const;

    // Work with window
    void startTextInput() const;
    void stopTextInput() const;
    void updateTitle() const;
};


// Temlates realisation
template <typename ...Args>
void Window::drawDebugText(float _X, float _Y, const char* _text, const Args& ..._args) const {
    SDL_RenderDebugTextFormat(renderer, _X, _Y, _text, _args...);
}
