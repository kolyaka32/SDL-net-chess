/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Types of language
enum LNG_types : unsigned {
    LNG_ENGLISH,     // English language
    LNG_RUSSIAN,     // Russian language
    LNG_GERMAN,      // German language
    LNG_BELARUSIAN,  // Belarusian language

    LNG_count,       // Counter of all languages
};

// Selected language of current app
extern LNG_types currentLanguage;
