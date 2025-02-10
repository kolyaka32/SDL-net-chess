/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "loader/dataLoader.hpp"
#include "../soundsNames.hpp"

// 
class Sounds
{
private:
    void loadSound();
public:
    Sounds(const DataLoader& loader);
    ~Sounds();
    void playSound();
};
