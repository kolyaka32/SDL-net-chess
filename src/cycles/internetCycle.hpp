/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../game/connectionLostBox.hpp"
#include "../game/terminatedBox.hpp"


// Cycle with game part of internet connection
class InternetCycle : public GameCycle {
protected:
    // Flag of running of current cycle
    static bool currentTurn;

    // Graphical part
    GUI::StaticText playersTurnsTexts[2];
    ConnectionLostBox disconnectedBox;
    TerminatedBox termianatedBox;
    GUI::StaticText winText;
    GUI::StaticText looseText;

public:
    InternetCycle(const App& app);
};
