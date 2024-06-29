/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "base.hpp"
#include "internet/internetServer.hpp"

// Game cycle (start server)
class ServerGameCycle : public InternetServerCycle {
 private:
    bool waitStart = true;    // Flag of waiting for game start
    bool waitTurn = false;    // Flag of waiting for another player for turn
    bool getData() override;  // Overloaded function of getting internet data

    // GUI objects
    GUI::StaticText waitText{"Wait for connection\0Ожидайте подключения\0auf Verbindung warten\0дачакайцеся злучэння",
       30, 0.5, 0.2, WHITE};
    GUI::StaticText portText{"Your port: %u\0Ваш порт: %u\0Ihr Hafen: %u\0Ваш партвейн: %u",
       30, 0.5, 0.4, WHITE};
    GUI::TextButton cancelButton{"Cancel\0Отмена\0Stornieren\0Адмяняць",
       24, 0.5, 0.9, WHITE};

 protected:
    // Overrided cycle functions
    bool getMouseInput() override;
    void draw() const override;

 public:
    ServerGameCycle();
    ~ServerGameCycle();
};
