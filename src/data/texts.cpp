/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "texts.hpp"


// Class of updation location
UpdateList::UpdateList() {}

// Adding new pointer to array
void UpdateList::add(GUI::GUItemplate* object) {
    // Adding new item, if possible
    if (size < maxSize) {
        languageUpdateList[size] = object;
        size++;
    }
}

// Entering internal cycle
void UpdateList::enterCycle() {
    // Setting new null elemnt to control
    languageUpdateList[size] = nullptr;
    size++;
}

// Exiting internal cycle
void UpdateList::exitCycle() {
    // Clearing allow to previous nullptr
    for (; (size > 0) && (languageUpdateList[--size]);) {}
}

// Updating all allowable objects
void UpdateList::update() {
    // Updating all objects
    for (Uint8 i=0; i < size; ++i) {
        if (languageUpdateList[i]) {
            languageUpdateList[i]->updateLocation();
        }
    }
}


// Texts class
// Global static texts
Texts::Texts() {
    updateTitle();
}

// Update translations of all texts
void Texts::updateTranslation() {
    updateTitle();

    // Updating texts
    updateList.update();
}

// Updating title depend on language
void Texts::updateTitle() {
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
