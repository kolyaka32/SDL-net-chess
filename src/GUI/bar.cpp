#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "baseGUI.hpp"
#include "../process.hpp"

using namespace GUI;


// Bar class
Bar::Bar( const SDL_Rect _rect, SDL_Color _color, IMG_names _icone ){
    // Base bar
    rect = _rect;
    Front_rect = _rect;
    color = _color;

    // Icone part
    if(_icone){
        texture = process.textures[_icone];  // Texture of icone
        IconeRect = rect;
        //SDL_QueryTexture(IconeTexture, NULL, NULL, &IconeRect.w, &IconeRect.h);
        //IconeRect.w = 14;
        //IconeRect.h = 16;

        IconeRect.y -= 2;
        IconeRect.x -= IconeRect.w + 2;
    }
};

void Bar::blit(int width){
    Front_rect.w = width;  // Setting width
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
    // Drawing back part
    SDL_RenderFillRect(renderer, &rect);  
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);  
    // Drawing front part
    SDL_RenderFillRect(renderer, &Front_rect);
    // Drawing icone
    if(texture){
        SDL_RenderCopy(renderer, texture, NULL, &IconeRect);
    }
};
