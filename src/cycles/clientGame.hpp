/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../internet/client.hpp"


// Game cycle (for single player (special animation))
class ClientGame : public BaseCycle {
 private:
    App& app;

    // Main run functions
    void inputMouseDown(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ClientGame(App& app);
};
