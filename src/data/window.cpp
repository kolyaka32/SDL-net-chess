/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "window.hpp"
#include "../define.hpp"


Window::Window(int _width, int _height, const LanguagedText _title)
: width(_width),
height(_height),
window(SDL_CreateWindow(titleText.getString().c_str(), width, height, 0)),
renderer(SDL_CreateRenderer(window, NULL)),
#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
textures{renderer},
#endif
#if (USE_SDL_FONT) && (PRELOAD_FONTS)
fonts{},
#endif
#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
animations{},
#endif
titleText(_title) {
    // Checking on correction of created objects
    #if (CHECK_CORRECTION)
    if (window == NULL) {
        logImportant("Can't create window");
    }
    #endif

    // Creating renderer from window
    #if (CHECK_CORRECTION)
    if (renderer == NULL) {
        logImportant("Can't create renderer");
    }
    #endif
}

Window::~Window() noexcept {
    // Destroying renderer
    SDL_DestroyRenderer(renderer);

    // Destrying window
    SDL_DestroyWindow(window);
}


// Work with window sizes
int Window::getWidth() const {
    return width;
}

int Window::getHeight() const {
    return height;
}

void Window::setWidth(int _width) {
    width = _width;
    SDL_SetWindowSize(window, width, height);
}

void Window::setHeight(int _height) {
    height = _height;
    SDL_SetWindowSize(window, width, height);
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

void Window::copyTexture(SDL_Texture* _dest, SDL_Texture* _src) const {
    setRenderTarget(_dest);
    SDL_RenderTexture(renderer, _src, nullptr, nullptr);
    resetRenderTarget();
}

void Window::blit(SDL_Texture* _texture, const SDL_FRect& _dest) const {
    SDL_RenderTexture(renderer, _texture, nullptr, &_dest);
}

void Window::blit(SDL_Texture* _texture, const SDL_FRect* _dest, const SDL_FRect* _src) const {
    SDL_RenderTexture(renderer, _texture, _src, _dest);
}

void Window::blit(SDL_Texture* _texture, float _angle, const SDL_FRect& _dest,
    const SDL_FRect* _src, SDL_FPoint _center) const {
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


// Work with loaded data
#if (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)
SDL_Texture* Window::getTexture(Textures _name) const {
    return textures[_name];
}
#endif  // (USE_SDL_IMAGE) && (PRELOAD_TEXTURES)


// Work with preloaded animations
#if (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)
IMG_Animation* Window::getAnimation(Animations _name) const {
    return animations[_name];
}
#endif  // (USE_SDL_IMAGE) && (PRELOAD_ANIMATIONS)


// Work with fonts
#if (USE_SDL_FONT) && (PRELOAD_FONTS)
TTF_Font* Window::getFont(Fonts _name) const {
    return fonts[_name];
}

TTF_Font* Window::createFontCopy(Fonts _name, float _height) const {
    TTF_Font* font = TTF_CopyFont(fonts[_name]);
    TTF_SetFontSize(font, _height);
    return font;
}

SDL_Texture* Window::createTexture(Fonts _font, float _height, const char* _text,
    unsigned _length, Color _color) const {
    // Setting text draw height
    TTF_SetFontSize(getFont(_font), _height);

    // Creating surface
    SDL_Surface* surface = TTF_RenderText_Solid(getFont(_font), _text, _length, _color);

    // Creating texture from created surface
    SDL_Texture* texture = createTexture(surface);

    SDL_DestroySurface(surface);
    return texture;
}

SDL_Texture* Window::createTexture(TTF_Font* _font, const char* _text, Color _color) const {
    // Creating surface
    SDL_Surface* surface = TTF_RenderText_Solid(_font, _text, 0, _color);

    // Creating texture from created surface
    SDL_Texture* texture = createTexture(surface);

    SDL_DestroySurface(surface);
    return texture;
}
#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)


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

void Window::updateTitle() const {
    updateTitle(titleText.getString().c_str());
}
