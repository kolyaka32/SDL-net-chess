/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include <SDL3_net/SDL_net.h>

// Game cycle (for single player (special animation))
class Server : public BaseCycle {
 private:
    App& app;

    SDLNet_DatagramSocket* server;

    // Main run functions
    void getMouseInput(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    Server(App& app);
    ~Server();
};
