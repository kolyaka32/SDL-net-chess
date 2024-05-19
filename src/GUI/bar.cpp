/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "../data/data.hpp"
#include "baseGUI.hpp"

using namespace GUI;


// Bar class
// Creating bar object
Bar::Bar(const SDL_Rect _rect, SDL_Color _color, IMG_names _icone)
: color(_color), Front_rect(_rect) {
    // Base bar
    rect = _rect;

    // Icone part
    if (_icone) {
        texture = data.textures[_icone];  // Texture of icone
        IconeRect = rect;
        // SDL_QueryTexture(IconeTexture, NULL, NULL, &IconeRect.w, &IconeRect.h);
        // IconeRect.w = 14;
        // IconeRect.h = 16;

        IconeRect.y -= 2;
        IconeRect.x -= IconeRect.w + 2;
    }
}

// Overriding blitting function
void Bar::blit(int width) {
    // Setting width
    Front_rect.w = width;

    // Drawing back part
    data.setColor(WHITE);
    SDL_RenderFillRect(data.renderer, &rect);

    // Drawing front part
    data.setColor(color);
    SDL_RenderFillRect(data.renderer, &Front_rect);

    // Drawing icone
    if (texture) {
        SDL_RenderCopy(data.renderer, texture, NULL, &IconeRect);
    }
}
