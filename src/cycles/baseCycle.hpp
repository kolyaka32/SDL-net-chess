/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/cycleTemplate.hpp"

//
class BaseCycle : public CycleTemplate
{
protected:
    Uint8 selectedBox;      // Number of which box is currently selected
    const MUS_names music;  // Music track to play (or NULL, if not need start)
public:
    BaseCycle(MUS_names song = MUS_START_NONE);
};
