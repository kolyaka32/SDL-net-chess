/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "dataLoader.hpp"


// Class of simplier implimintation of loading file, straight from file
class StraightLoader : public DataLoader {
public:
    StraightLoader();
    ~StraightLoader() override;
    SDL_IOStream* load(const char* name) const override;
};
