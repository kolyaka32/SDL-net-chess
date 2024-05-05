#include "letters.hpp"

#include "../../data/data.hpp"


// Class with letters, placed in collumn
LettersCollumn::LettersCollumn(const char _startLetter, const Uint8 _length, Uint8 _xOffset, Uint8 _yOffset){
    // Locking thread for start
    data.drawMutex.lock();

    // Creating font (if need)
    if(!font){
        font = data.createFont(20);
    }
    // Creating main texture
    texture = SDL_CreateTexture(data.renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, 
        _xOffset ? _length * CELL_SIDE : LETTER_LINE, _yOffset ? _length * CELL_SIDE : LETTER_LINE);
    
    // Setting tearget to render to this texture
    SDL_SetRenderTarget(data.renderer, texture);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    // Creating collumn of letters
    for(Uint8 i=0; i < _length; ++i){
        // Creating surface with need letter
        const char text[2] = {(char)(_startLetter + i), '\0'};  // Text for surface
        SDL_Surface* letterSurface = TTF_RenderUTF8_Shaded(font, text, WHITE, BLACK);

        // Creating texture from this surface
        SDL_Texture* letterTexture = SDL_CreateTextureFromSurface(data.renderer, letterSurface);

        // Updating texture parametrs
        SDL_Rect dest = {_xOffset*i+4, _yOffset*i-4, 0, 0};
        SDL_QueryTexture(letterTexture, NULL, NULL, &dest.w, &dest.h);

        // Copying texture to main texture
        SDL_RenderCopy(data.renderer, letterTexture, nullptr, &dest);

        // Freeing temp data
        SDL_DestroyTexture(letterTexture);
        SDL_FreeSurface(letterSurface);
    }

    // Setting texture for using
    SDL_UnlockTexture(texture);

    // Unlocking render
    SDL_SetRenderTarget(data.renderer, nullptr);

    // Resetting mutex
    data.drawMutex.unlock();
};

// Savely clear all rest data
LettersCollumn::~LettersCollumn(){
    // Locking any side processes
    data.drawMutex.lock();

    // Clearing texture
    SDL_DestroyTexture(texture);

    // Unlocking side proceses after work
    data.drawMutex.unlock();
};



// Class of drawing board frame with letters for better UI
SurroundingLetters::SurroundingLetters(){
    
};

SurroundingLetters::~SurroundingLetters(){
    
};

void SurroundingLetters::blit() const{
    // Drawing numbers
    // Left collumn
    const static SDL_Rect column1 = {0, UPPER_LINE - LETTER_LINE/2 + CELL_SIDE/2, LETTER_LINE, GAME_HEIGHT};
    SDL_RenderCopy(data.renderer, numberCollumn.texture, nullptr, &column1);

    // Right column
    const static SDL_Rect column2 = {SCREEN_WIDTH-RIGHT_LINE, UPPER_LINE - LETTER_LINE/2 + CELL_SIDE/2, LETTER_LINE, GAME_HEIGHT};
    SDL_RenderCopy(data.renderer, numberCollumn.texture, nullptr, &column2);

    // Drawing letters
    // Upper collumn
    const static SDL_Rect column3 = {LEFT_LINE/2 + CELL_SIDE/2, UPPER_LINE - LETTER_LINE, GAME_WIDTH, LETTER_LINE};
    SDL_RenderCopy(data.renderer, letterCollumn.texture, nullptr, &column3);

    // Bottom column
    const static SDL_Rect column4 = {LEFT_LINE/2 + CELL_SIDE/2, SCREEN_HEIGHT - DOWN_LINE, GAME_WIDTH, LETTER_LINE};
    SDL_RenderCopy(data.renderer, letterCollumn.texture, nullptr, &column4);
};

