/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Types of language
enum LNG_types{
    LNG_ENGLISH,    // English language
    LNG_RUSSIAN,    // Russian language
    LNG_GERMAN,     // German language
    LNG_BELARUSIAN  // Belarusian language
};

// Data type for language
typedef unsigned char language;

#define LNG_count 4  // Final counter of all languages
