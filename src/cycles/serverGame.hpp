/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "gameCycle.hpp"
#include "../internet/gameConnection.hpp"


// Game cycle with game part of server
class ServerGame : public GameCycle {
 private:
    GameConnection connection;

    // Main run functions
    void inputMouseDown(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ServerGame(App& app, Connection& server);
};
