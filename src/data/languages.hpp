/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>
#include "../languagesNames.hpp"


// Class, storing one text variant in different locations
class LanguagedText {
private:
    static Language currentLanguage;
    const std::string textVariants[(unsigned)Language::Count];

public:
    LanguagedText(const std::string englishVariant, const std::string russianVariant,
        const std::string germanVariant, const std::string bellarussianVariant);
    const std::string& getString() const;
    // Options for change current language
    static bool setLanguage(Language newLanguage);
    static Language getLanguage();
};
