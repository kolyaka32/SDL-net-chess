#include "../include.hpp"
#include "../define.hpp"
#include "../values.hpp"
#include "baseGUI.hpp"
#include "../graphics.hpp"
#include "../process.hpp"

using namespace GUI;


// Bar class
Bar::Bar( const SDL_Rect dest, SDL_Color newColor, IMG_names icone ){
    // Base bar
    Back_rect = dest;
    Front_rect = dest;
    color = newColor;

    // Icone part
    if(icone){
        IconeTexture = process.graphics[icone];  // Texture of icone
        IconeRect = dest;
        //SDL_QueryTexture(IconeTexture, NULL, NULL, &IconeRect.w, &IconeRect.h);
        //IconeRect.w = 14;
        //IconeRect.h = 16;

        IconeRect.y -= 2;
        IconeRect.x -= IconeRect.w + 2;
    }
};

void Bar::blit(int width){
    Front_rect.w = width;  // Setting width
    SDL_SetRenderDrawColor(process.app.renderer, 255, 255, 255, 255);  
    // Drawing back part
    SDL_RenderFillRect(process.app.renderer, &Back_rect);  
    SDL_SetRenderDrawColor(process.app.renderer, color.r, color.g, color.b, color.a);  
    // Drawing front part
    SDL_RenderFillRect(process.app.renderer, &Front_rect);
    // Drawing icone
    if(IconeTexture){
        SDL_RenderCopy(process.app.renderer, IconeTexture, NULL, &IconeRect);
    }
};
