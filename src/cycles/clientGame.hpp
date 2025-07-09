/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../internet/gameConnection.hpp"


// Game cycle (for single player (special animation))
class ClientGame : public GameCycle {
 private:
    GameConnection connection;
    static bool currentTurn;

    // Main run functions
    void inputMouseDown(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ClientGame(App& app, Connection& client);
};
