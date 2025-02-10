/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "window.hpp"
#include "../define.hpp"
#include "exceptions.hpp"


Window::Window(const DataLoader& _loader)
 : textures{_loader},
 fonts{_loader} {
    // Creating showing tools
    SDL_CreateWindowAndRenderer(WINDOWNAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

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




void Window::setDrawColor(SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Window::clear() {
    SDL_RenderClear(renderer);
}

void Window::render() {
    SDL_RenderPresent(renderer);
}


void Window::drawPoint(float x, float y) {
    SDL_RenderPoint(renderer, x, y);
}

void Window::drawRect(const SDL_FRect& _rect) {
    SDL_RenderFillRect(renderer, &_rect);
}


SDL_Texture* Window::getTexture(IMG_names _name) {
    return textures[_name];
}


SDL_Texture* Window::createTexture(int _width, int _height, SDL_TextureAccess _access, SDL_PixelFormat _format) {
    return SDL_CreateTexture(renderer, _format, _access, _width, _height);
}

SDL_Texture* Window::createTexture(SDL_Surface* _surface, bool isFree) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, _surface);
    if (isFree) {
        SDL_DestroySurface(_surface);
    }
    return texture;
}

void Window::blit(SDL_Texture* _texture, const SDL_FRect* _dest, const SDL_FRect* _src) {
    SDL_RenderTexture(renderer, _texture, _src, _dest);
}

void Window::blit(SDL_Texture* _texture, float _angle, const SDL_FRect* _dest, const SDL_FRect* _src, SDL_FPoint _center) {
    SDL_RenderTextureRotated(renderer, _texture, _src, _dest, _angle, &_center, SDL_FLIP_NONE);
}

void Window::setRenderTarget(SDL_Texture* _target) {
    SDL_SetRenderTarget(renderer, _target);
}

void Window::resetRenderTarget() {
    SDL_SetRenderTarget(renderer, nullptr);
}

void Window::setBlendMode(SDL_Texture* _texture, SDL_BlendMode _blendMode) {
    SDL_SetTextureBlendMode(_texture, _blendMode);
}

void Window::unlockTexture(SDL_Texture* _texture) {
    SDL_UnlockTexture(_texture);
}

void Window::destroyTexture(SDL_Texture* _texture) {
    SDL_DestroyTexture(_texture);
}


void Window::blitText(const char* text, const SDL_FRect& rect) {

}
