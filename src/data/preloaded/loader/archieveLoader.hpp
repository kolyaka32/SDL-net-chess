/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../../../define.hpp"


// Check, if need to load data from archieve
#if (PRELOAD_DATA) && (ARCHIEVE_LOADING)

#include <zip.h>
#include <SDL3/SDL_iostream.h>


// Implimentation of loader for arcives
class ArchieveLoader {
 private:
    const char* password = nullptr;  // Absence of password
    zip_t* archive;  // Archive, where data is located

 public:
    ArchieveLoader();
    ~ArchieveLoader();
    SDL_IOStream* load(const char* name) const;
};

#endif  // (PRELOAD_DATA) && (ARCHIEVE_LOADING)
