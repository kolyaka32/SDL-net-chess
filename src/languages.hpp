/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Types of language
enum LNG_types{
    LNG_ENGLISH,     // English language
    LNG_RUSSIAN,     // Russian language
    LNG_GERMAN,      // German language
    LNG_BELARUSIAN,  // Belarusian language

    LNG_count,       // Global counter of all languages
};

// Data type for language
typedef unsigned char language;
