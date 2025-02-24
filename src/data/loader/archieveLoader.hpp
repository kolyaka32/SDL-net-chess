/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "dataLoader.hpp"
#include "zip.h"


// Setting password for archive
#define ARCHIEVE_PASSWORD NULL

// Implimentation of loader for arcives
class ArchieveLoader : public DataLoader {
private:
    zip_t* archive;  // Archive, where data is located
public:
    ArchieveLoader();
    ~ArchieveLoader() override;
    SDL_IOStream* load(const char* name) const override;
};
