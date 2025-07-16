/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"

// Function for setting window title depend on language
void Window::updateTitle() const {
    // Setting window title
    switch (LanguagedText::getLanguage()) {
    case Language::English:
        updateTitle("Chess on SDL");
        break;

    case Language::Russian:
        updateTitle("Шахматы на SDL");
        break;

    case Language::German:
        updateTitle("Schach на SDL");
        break;

    case Language::Bellarusian:
        updateTitle("Шахматы на SDL");
        break;
    }
}
