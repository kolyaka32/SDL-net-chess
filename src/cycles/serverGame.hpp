/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"
#include "../internet/gameConnection.hpp"


// Game cycle with game part of server
class ServerGame : public InternetCycle {
 protected:
    GameConnection connection;

    // Main run functions
    void inputMouseDown(App& app) override;
    void inputKeys(App& app, SDL_Keycode key);
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ServerGame(App& app, Connection& server);
};
