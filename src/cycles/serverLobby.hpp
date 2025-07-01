/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include <SDL3_net/SDL_net.h>


// Cycle with waiting for client connect
class ServerLobby : public BaseCycle {
 private:
    App& app;

    NET_DatagramSocket* server;

    // Title
    GUI::StaticText titleText;

    // Text with current connection address
    const char* currentAddress = nullptr;
    GUI::DynamicText addressText;
    GUI::InfoBox copiedInfoBox;
    bool showAddress = false;
    GUI::TextButton showAddressText;
    GUI::TextButton hideAddressText;

    // Main run functions
    void inputMouseDown(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ServerLobby(App& app);
    ~ServerLobby();
};
