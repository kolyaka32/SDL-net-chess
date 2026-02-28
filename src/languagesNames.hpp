/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Selectable languages to use
enum class Language : unsigned {
    English,
    Russian,
    German,
    Bellarusian,

    // Counter of all languages
    Count,

    // Standart pre-selected language
    Default = English
};
