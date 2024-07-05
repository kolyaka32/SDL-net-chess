/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"


// Class of game client
class InternetClientCycle : public InternetCycle {
 public:
    InternetClientCycle();
    ~InternetClientCycle();

    Uint8 tryConnect(const char* ipText, const char* portText);  // Return 1, if connected
};
