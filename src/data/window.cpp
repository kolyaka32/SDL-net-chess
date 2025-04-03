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
 : window(SDL_CreateWindow(WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, 0)),
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


void Window::setDrawColor(Color color) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Window::clear() const {
    SDL_RenderClear(renderer);
}

void Window::render() const {
    SDL_RenderPresent(renderer);
}



// Work with loaded data
SDL_Texture* Window::getTexture(IMG_names _name) const {
    return textures[_name];
}

IMG_Animation* Window::getAnimation(ANI_names _name) const {
    return animations[_name];
}



// Draw basic geometric shapes
void Window::drawPoint(float x, float y) const {
    SDL_RenderPoint(renderer, x, y);
}

void Window::drawRect(const SDL_FRect& _rect) const {
    SDL_RenderFillRect(renderer, &_rect);
}

void Window::drawLine(float x1, float y1, float x2, float y2) const {
    SDL_RenderLine(renderer, x1, y1, x2, y2);
}



// Work with surfaces
SDL_Surface* Window::createSurface(int _width, int _height, SDL_PixelFormat _format) const {
    return SDL_CreateSurface(_width, _height, _format);
}

void Window::setBlendMode(SDL_Surface* _surface, SDL_BlendMode _blendMode) const {
    SDL_SetSurfaceBlendMode(_surface, _blendMode);
}

void Window::destroy(SDL_Surface* _surface) const {
    SDL_DestroySurface(_surface);
}



// Work with loaded textures
void Window::blit(IMG_names _index, const SDL_FRect& _dest, const SDL_FRect* _src) const {
    SDL_RenderTexture(renderer, textures[_index], _src, &_dest);
}

void Window::blit(IMG_names _index, float _angle, const SDL_FRect& _dest, const SDL_FRect* _src, SDL_FPoint _center) const {
    SDL_RenderTextureRotated(renderer, textures[_index], _src, &_dest, _angle, &_center, SDL_FLIP_NONE);
}

void Window::setBlendMode(IMG_names _index, SDL_BlendMode _blendMode) const {
    SDL_SetTextureBlendMode(textures[_index], _blendMode);
}

void Window::setColorMode(IMG_names _index, Color _color) const {
    SDL_SetTextureColorMod(textures[_index], _color.r, _color.g, _color.b);
}



// Work with side textures
SDL_Texture* Window::createTexture(int _width, int _height, SDL_TextureAccess _access, SDL_PixelFormat _format) const {
    return SDL_CreateTexture(renderer, _format, _access, _width, _height);
}

SDL_Texture* Window::createTexture(SDL_Surface* _surface) const {
    return SDL_CreateTextureFromSurface(renderer, _surface);
}

SDL_Texture* Window::createTextureAndFree(SDL_Surface* _surface) const {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, _surface);
    SDL_DestroySurface(_surface);
    return texture;
}

void Window::blit(SDL_Texture* _texture, const SDL_FRect& _dest, const SDL_FRect* _src) const {
    SDL_RenderTexture(renderer, _texture, _src, &_dest);
}

void Window::blit(SDL_Texture* _texture, float _angle, const SDL_FRect& _dest, const SDL_FRect* _src, SDL_FPoint _center) const {
    SDL_RenderTextureRotated(renderer, _texture, _src, &_dest, _angle, &_center, SDL_FLIP_NONE);
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

void Window::setColorMode(SDL_Texture* _texture, Color _color) const {
    SDL_SetTextureColorMod(_texture, _color.r, _color.g, _color.b);
}

void Window::unlock(SDL_Texture* _texture) const {
    SDL_UnlockTexture(_texture);
}

void Window::destroy(SDL_Texture* _texture) const {
    SDL_DestroyTexture(_texture);
}



// Work with fonts
TTF_Font* Window::getFont(FNT_names _name) const {
    return fonts[_name];
}

TTF_Font* Window::createFontCopy(FNT_names _name, float _height) const {
    TTF_Font* font = TTF_CopyFont(fonts[_name]);
    TTF_SetFontSize(font, _height);
    return font;
}

SDL_Texture* Window::createTexture(FNT_names _font, float _height, const char* _text, unsigned _length, Color _color) const {
    // Setting text draw height
    TTF_SetFontSize(getFont(_font), _height);

    // Creating surface
    SDL_Surface* surface = TTF_RenderText_Solid(getFont(_font), _text, _length, _color);

    // Creating texture from created surface
    SDL_Texture* texture = createTexture(surface);

    SDL_DestroySurface(surface);
    return texture;
}


// Work with text inputing
void Window::startTextInput() const {
    SDL_StartTextInput(window);
}

void Window::stopTextInput() const {
    SDL_StopTextInput(window);
}

void Window::updateTitle(const char* _name) const {
    SDL_SetWindowTitle(window, _name);
}
