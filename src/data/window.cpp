/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "window.hpp"
#include "../define.hpp"
#include "exceptions.hpp"

// Names of loading files
#include "../texturesNames.hpp"
#include "../fontsNames.hpp"
#include "../languages.hpp"


Window::Window(const DataLoader& _loader)
 : window(SDL_CreateWindow(WINDOWNAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0)),
renderer(SDL_CreateRenderer(window, NULL)),
textures{_loader, renderer, IMG_count, texturesFilesNames},
fonts{_loader, FNT_count, fontsFilesNames},
animations{_loader, ANI_count, animationsFilesNames} {
    // Checking on correction of created objects
    #if CHECK_CORRECTION
    if (window == NULL) {
        throw LibararyLoadException("window creation");
    }
    #endif

    // Creating renderer from window
    #if CHECK_CORRECTION
    if (renderer == NULL) {
        throw LibararyLoadException("renderer creation");
    }
    #endif
}

Window::~Window() noexcept {
    // Destroying renderer
    SDL_DestroyRenderer(renderer);

    // Destrying window
    SDL_DestroyWindow(window);
}


void Window::setDrawColor(SDL_Color color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Window::clear() const {
    SDL_RenderClear(renderer);
}

void Window::render() const {
    SDL_RenderPresent(renderer);
}


void Window::drawPoint(float x, float y) const {
    SDL_RenderPoint(renderer, x, y);
}

void Window::drawRect(const SDL_FRect& _rect) const {
    SDL_RenderFillRect(renderer, &_rect);
}


SDL_Texture* Window::getTexture(IMG_names _name) const {
    return textures[_name];
}

IMG_Animation* Window::getAnimation(ANI_names _name) const {
    return animations[_name];
}


SDL_Surface* Window::createSurface(int _width, int _height, SDL_PixelFormat _format) const {
    return SDL_CreateSurface(_width, _height, _format);
}

SDL_Texture* Window::createTexture(int _width, int _height, SDL_TextureAccess _access, SDL_PixelFormat _format) const {
    return SDL_CreateTexture(renderer, _format, _access, _width, _height);
}

SDL_Texture* Window::createTexture(SDL_Surface* _surface, bool isFree) const {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, _surface);
    if (isFree) {
        SDL_DestroySurface(_surface);
    }
    return texture;
}

void Window::blit(SDL_Texture* _texture, const SDL_FRect& _dest, const SDL_FRect* _src) const {
    SDL_RenderTexture(renderer, _texture, _src, &_dest);
}

void Window::blit(SDL_Texture* _texture, float _angle, const SDL_FRect& _dest, const SDL_FRect* _src, SDL_FPoint _center) const {
    SDL_RenderTextureRotated(renderer, _texture, _src, &_dest, _angle, &_center, SDL_FLIP_NONE);
}

void Window::blit(IMG_names _name, const SDL_FRect& _dest, const SDL_FRect* _src) const {
    SDL_RenderTexture(renderer, textures[_name], _src, &_dest);
}

void Window::setRenderTarget(SDL_Texture* _target) const {
    SDL_SetRenderTarget(renderer, _target);
}

void Window::resetRenderTarget() const {
    SDL_SetRenderTarget(renderer, nullptr);
}

void Window::setBlendMode(SDL_Texture* _texture, SDL_BlendMode _blendMode) const {
    SDL_SetTextureBlendMode(_texture, _blendMode);
}

void Window::unlockTexture(SDL_Texture* _texture) const {
    SDL_UnlockTexture(_texture);
}

void Window::destroyTexture(SDL_Texture* _texture) const {
    SDL_DestroyTexture(_texture);
}


TTF_Font* Window::getFont(FNT_names _name) const {
    return fonts[_name];
}

TTF_Font* Window::createFontCopy(FNT_names _name, float _height) const {
    TTF_Font* font = TTF_CopyFont(fonts[_name]);
    TTF_SetFontSize(font, _height);
    return font;
}

SDL_Texture* Window::createTexture(FNT_names _font, float _height, const char* _text, unsigned _length, SDL_Color _color) const {
    // Setting text draw height
    TTF_SetFontSize(getFont(_font), _height);

    // Creating surface
    SDL_Surface* surface = TTF_RenderText_Solid(getFont(_font), _text, _length, _color);

    // Creating texture from created surface
    SDL_Texture* texture = createTexture(surface);

    SDL_DestroySurface(surface);
    return texture;
}


void Window::startTextInput() const {
    SDL_StartTextInput(window);
}

void Window::stopTextInput() const {
    SDL_StopTextInput(window);
}

void Window::updateTitle() const {
    // Setting window title
    switch (currentLanguage) {
    case LNG_ENGLISH:
        updateTitle("Chess on SDL");
        break;

    case LNG_RUSSIAN:
        updateTitle("Шахматы на SDL");
        break;

    case LNG_GERMAN:
        updateTitle("Schach на SDL");
        break;

    case LNG_BELARUSIAN:
        updateTitle("Шахматы на SDL");
        break;
    }
}

void Window::updateTitle(const char* _name) const {
    SDL_SetWindowTitle(window, _name);
}
