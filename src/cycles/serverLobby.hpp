/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../internet/server.hpp"


// Cycle with waiting for client connect
class ServerLobby : public BaseCycle {
 private:
    // Internet connection part
    Server server;

    // Title
    GUI::StaticText titleText;

    // Text with current connection address
    char currentAddress[24];          // String with current app address for connection
    static bool showAddress;          // Flag of showing current address to screen
    GUI::DynamicText addressText;     // Text for showing/copying current address
    GUI::InfoBox copiedInfoBox;       // Message about copying to clipboard address
    GUI::TextButton showAddressText;  // Buttons to change state of showing address at screen
    GUI::TextButton hideAddressText;

    // Main run functions
    void inputMouseDown(App& app) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ServerLobby(App& app);
};
