/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;

// Class of static text
HighlightedStaticText::HighlightedStaticText(const Window& _target, const std::string (&_text)[LNG_count], float _height,
    float _X, float _Y, int frame, SDL_Color _color, ALIGNMENT_types _aligment) {
    // Creating texture of text
    TTF_Font* font = _target.getFont(FNT_MAIN);
    TTF_SetFontSize(font, _height);
    TTF_SetFontOutline(font, frame);

    // Creating surface
    SDL_Surface* surface = TTF_RenderText_Solid(font, _text[currentLanguage].c_str(), 0, {1, 0, 0, 255});
    
    // Resetting outline
    TTF_SetFontOutline(font, 0);
    SDL_Surface* frontSurface = TTF_RenderText_Solid(font, _text[currentLanguage].c_str(), 0, _color);

    // Merging surfaces
    SDL_SetSurfaceBlendMode(frontSurface, SDL_BLENDMODE_NONE);
    SDL_BlitSurface(frontSurface, nullptr, surface, nullptr);
    SDL_DestroySurface(frontSurface);

    // Creating texture from created surface
    texture = _target.createTexture(surface);

    // Updating rect height for correct button
    SDL_GetTextureSize(texture, &rect.w, &rect.h);
    rect.x = SDL_roundf(SCREEN_WIDTH * _X - (rect.w * _aligment / 2));
    rect.y = SDL_roundf(SCREEN_HEIGHT * _Y - rect.h / 2);
}

HighlightedStaticText::~HighlightedStaticText() {
    SDL_DestroyTexture(texture);
}
