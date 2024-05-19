/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "base.hpp"
#include "internet/internetServer.hpp"

// Main game cycle (start like server)
class ServerGameCycle : public InternetServerCycle {
 private:
    bool waitStart = true;     // Flag of waiting for game start
    bool waitTurn = false;     // Flag of waiting for another player for turn
    Uint8 getData() override;  // Overloaded function of getting internet data

 protected:
    // New overrided cycle functions
    Uint8 mouseInput() override;  // Checking for any need mouse action
    void draw() const override;   // Drawing all needed objects

 public:
    ServerGameCycle();
    ~ServerGameCycle();
};
