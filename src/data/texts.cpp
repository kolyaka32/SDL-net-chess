#include "texts.hpp"

// Global static texts
Texts::Texts(){
    updateTranslation();
};

Texts::~Texts(){

}

void Texts::updateTranslation(){
    // Setting fruit skin
    switch (language)
    {
    case LNG_ENGLISH:
        SDL_SetWindowTitle(window, "Chess on SDL");
        break;

    case LNG_RUSSIAN:
        SDL_SetWindowTitle(window, "Шахматы на SDL");
        break;

    case LNG_GERMAN:
        SDL_SetWindowTitle(window, "--- на SDL");
        break;

    case LNG_BELARUSIAN:
        SDL_SetWindowTitle(window, "--- на SDL");
        break;
    }
    
    // Updating texts
    for(Uint8 i = 0; i < TXT_count; ++i){
        texts[i].updateText();
    }
}
