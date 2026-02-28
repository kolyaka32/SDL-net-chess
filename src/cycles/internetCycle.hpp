/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../internet/internet.hpp"


// Cycle with game part of internet connection
class InternetCycle : public GameCycle {
 protected:
    // Flag of running of current cycle
    static bool currentTurn;

    // Messages with internet state
    GUI::TwoOptionBox disconnectedBox;
    GUI::OneOptionBox termianatedBox;

    // Redefined current texts
    GUI::StaticText playersTurnsTexts[2];
    GUI::HighlightedStaticText winText;
    GUI::HighlightedStaticText looseText;

    virtual void getInternetPacket(const GetPacket& packet);

 protected:
    bool inputMouseDown() override;
    void update() override;

 public:
    InternetCycle(Window& window);
};
