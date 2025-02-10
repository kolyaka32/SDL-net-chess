/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "window.hpp"
#include "../define.hpp"
#include "exceptions.hpp"


Window::Window(const DataLoader& _loader)
 : textures{_loader},
 fonts{_loader}
{
    // Creating window
    window = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    #if CHECK_CORRECTION
    if (window == NULL) {
        throw LibararyLoadException("window creation");
    }
    #endif

    // Creating renderer from window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    #if CHECK_CORRECTION
    if (renderer == NULL) {
        throw LibararyLoadException("renderer creation");
    }
    #endif
}


Window::~Window() {
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


void Window::drawPoint(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void Window::drawRect(const SDL_Rect& _rect) {
    SDL_RenderFillRect(renderer, &_rect);
}

void Window::blit(IMG_names _name, const SDL_Rect* _dest, const SDL_Rect* _src) {
    SDL_RenderCopy(renderer, textures[_name], _src, _dest);
}

void Window::blit(IMG_names _name, float _angle, const SDL_Rect* _dest, const SDL_Rect* _src, SDL_Point _center) {
    SDL_RenderCopyEx(renderer, textures[_name], _src, _dest, _angle, &_center, SDL_FLIP_NONE);
}

void Window::queryTexture(IMG_names name, int* _width, int* _height) {
    SDL_QueryTexture(textures[name], nullptr, nullptr, _width, _height);
}


SDL_Texture* Window::createTexture(int _width, int _height, SDL_PixelFormatEnum _format) {
    return SDL_CreateTexture(renderer, _format, SDL_TEXTUREACCESS_TARGET, _width, _height);
}

void Window::blit(SDL_Texture* _texture, const SDL_Rect* _dest, const SDL_Rect* _src) {
    SDL_RenderCopy(renderer, _texture, _src, _dest);
}

void Window::setRenderTarget(SDL_Texture* _target) {
    SDL_SetRenderTarget(renderer, _target);
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


void Window::blitText(const char* text, const SDL_Rect& rect) {

}
