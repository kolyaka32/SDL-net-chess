/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../internet/gameConnection.hpp"


// Game cycle (for single player (special animation))
class ClientGame : public BaseCycle {
 private:
    GameConnection connection;

    // Main run functions
    void inputMouseDown(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ClientGame(App& app, Connection& client);
};
