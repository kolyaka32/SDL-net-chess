/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "languages.hpp"


// Initialasing static members
Language LanguagedText::currentLanguage = Language::Default;

LanguagedText::LanguagedText(const std::string englishVariant, const std::string russianVariant,
    const std::string germanVariant, const std::string bellarussianVariant)
: textVariants{englishVariant, russianVariant, germanVariant, bellarussianVariant} {}

const std::string& LanguagedText::getString() const {
    return textVariants[(unsigned)currentLanguage];
}

bool LanguagedText::setLanguage(Language _newLanguage) {
    if (currentLanguage != _newLanguage) {
        currentLanguage = _newLanguage;
        return true;
    }
    return false;
}

Language LanguagedText::getLanguage() {
    return currentLanguage;
}
