/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "languages.hpp"


// Initialasing static members
Language LanguagedText::currentLanguage = Language::Default;

LanguagedText::LanguagedText(const std::string englishVariant, const std::string russianVariant,
    const std::string germanVariant, const std::string bellarussianVariant)
: textVariants{englishVariant, russianVariant, germanVariant, bellarussianVariant} {}

LanguagedText::LanguagedText(const std::string singleVariant)
: textVariants{singleVariant, singleVariant, singleVariant, singleVariant} {}

LanguagedText::LanguagedText(const LanguagedText& _copyText) noexcept
: textVariants(_copyText.textVariants) {}

LanguagedText::LanguagedText(LanguagedText&& _movedText) noexcept
: textVariants(std::move(_movedText.textVariants)) {}

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
