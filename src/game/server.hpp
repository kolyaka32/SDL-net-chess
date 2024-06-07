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
    bool getData() override;  // Overloaded function of getting internet data

    // GUI objects
    GUI::StaticText waitText{"Wait for connection\0Ожидайте подключения\0-\0-",
       30, 0.5, 0.2, WHITE};
    GUI::StaticText portText{"Your port: %u\0Ваш порт: %u\0-%u\0-%u",
       30, 0.5, 0.4, WHITE};
    GUI::TextButton cancelButton{"Cancel\0Отмена\0-\0-",
       24, 0.5, 0.9, WHITE};

 protected:
    // New overrided cycle functions
    bool getMouseInput() override;  // Checking for any need mouse action
    void draw() const override;   // Drawing all needed objects

 public:
    ServerGameCycle();
    ~ServerGameCycle();
};
