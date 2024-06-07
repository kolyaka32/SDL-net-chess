/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>

#include "base.hpp"
#include "internet/internetClient.hpp"

//
class ClientGameCycle : public InternetClientCycle {
 private:
    bool waitStart = true;     // Flag of waiting for game start
    bool waitTurn = true;      // Flag of waiting for another player for turn
    timer lastTypeBoxUpdate;   // Timer for change symbol of caret

    bool getData() override;  // Overloaded function of getting internet data
    void removeSelection();    //
    
    // GUI objects
    GUI::StaticText enterIPText{"Enter IP:\0Введите IP:\0-\0-",
       30, 0.5, 0.1, WHITE};
    GUI::StaticText enterPortText{"Enter port:\0Введите порт:\0-\0-",
       30, 0.5, 0.4, WHITE};
    GUI::TextButton cancelButton{"Cancel\0Отмена\0-\0-",
       24, 0.5, 0.9, WHITE};
    GUI::TextButton connectButton{"Connect\0Присоединится\0-\0-",
       24, 0.5, 0.7, WHITE};

    // Input fields
    GUI::typeBox typeBoxes[2]{
        {20, 0.5, 0.2, data.baseIP.std::string::c_str()},
        {20, 0.5, 0.5, data.basePort.std::string::c_str()}
    };

 protected:
    // New overrided cycle functions
    // Getting special user input
    bool getMouseInput() override;  // Checking for any need mouse action
    bool getKeysInput(SDL_Keysym& key) override;  // Checking for any keys actions
    bool getAnotherInput(SDL_Event& event) override;  // Getting rest input
    void draw() const override;     // Drawing all needed objects
    void update() override;         // Special update

 public:
    ClientGameCycle();
    ~ClientGameCycle();
};
