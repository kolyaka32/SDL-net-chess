/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "texts.hpp"

// Global static texts
Texts::Texts() {
    updateTitle();
}

// Update translations of all texts
void Texts::updateTranslation() {
    updateTitle();
    
    // Updating texts
    for (Uint8 i = 0; i < TXT_count; ++i) {
        texts[i].updateText();
    }

    // Updating buttons
    for (Uint8 i = 0; i < BTN_count; ++i) {
        textButtons[i].updateLocation();
    }
}

// Updating title depend on language
void Texts::updateTitle(){
    // Setting window title
    switch (language) {
    case LNG_ENGLISH:
        SDL_SetWindowTitle(window, "Chess on SDL");
        break;

    case LNG_RUSSIAN:
        SDL_SetWindowTitle(window, "Шахматы на SDL");
        break;

    case LNG_GERMAN:
        SDL_SetWindowTitle(window, "Schach на SDL");
        break;

    case LNG_BELARUSIAN:
        SDL_SetWindowTitle(window, "Шахматы на SDL");
        break;
    }
}
