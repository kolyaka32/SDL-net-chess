/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>
#include <array>
#include "logger.hpp"
#include "../languagesNames.hpp"


// Class, storing one text variant in different locations
class LanguagedText {
 private:
    // Text in different languages
    const std::array<std::string, (unsigned)Language::Count> textVariants;
    // Currently selected language for whole app
    static Language currentLanguage;

 public:
    LanguagedText(const std::string englishVariant, const std::string russianVariant,
        const std::string germanVariant, const std::string bellarussianVariant);
    LanguagedText(const std::string singleVariant);
    LanguagedText(const LanguagedText& copyText) noexcept;
    LanguagedText(LanguagedText&& movedText) noexcept;
    const std::string& getString() const;
    // Options for change current language
    // Return true, if need to change language
    static bool setLanguage(Language newLanguage);
    static Language getLanguage();
};
