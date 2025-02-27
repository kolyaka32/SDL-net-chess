/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <string>

#include "gameCycle.hpp"
#include "../data/internet/internetClient.hpp"

// Class of game cycle for client with connection part
class ClientGameCycle : public InternetClientCycle {
 private:
    bool waitStart = true;     // Flag of waiting for game start
    bool waitTurn = true;      // Flag of waiting for another player for turn
    timer lastTypeBoxUpdate;   // Timer for change symbol of caret
    bool selecting = false;    // Flag of pressing on mouse to selecting text

    bool getData() override;   // Overloaded function of getting internet data
    void removeSelection();    // Function for reseting selection from type boxes

    // GUI objects
    GUI::StaticText enterIPText{"Enter IP:\0Введите IP:\0-\0Увядзіце IP:",
       30, 0.5, 0.1, WHITE};
    GUI::StaticText enterPortText{"Enter port:\0Введите порт:\0Port eingeben:\0Увядзіце порт:",
       30, 0.5, 0.4, WHITE};
    GUI::TextButton cancelButton{"Cancel\0Отмена\0Annullierung\0Адмена",
       24, 0.5, 0.9, WHITE};
    GUI::TextButton connectButton{"Connect\0Присоединится\0Beitritt\0Далучыцца",
       24, 0.5, 0.7, WHITE};

    // Input fields
    GUI::TypeBox typeBoxes[2]{
        {20, 0.5, 0.2, data.baseIP.std::string::c_str()},
        {20, 0.5, 0.5, data.basePort.std::string::c_str()}
    };

 protected:
    bool getMouseInput() override;
    bool getKeysInput(const SDL_Keysym& key) override;
    bool getAnotherInput(const SDL_Event& event) override;
    void draw() const override;
    void update() override;

 public:
    ClientGameCycle();
    ~ClientGameCycle();
};
