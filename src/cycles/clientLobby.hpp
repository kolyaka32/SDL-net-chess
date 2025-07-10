/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include "../internet/client.hpp"


// Global base connect link for type in typeboxes
extern char baseIP[12];
extern char basePort[6];

// Game cycle (for single player (special animation))
class ClientLobby : public BaseCycle {
 private:
    // Internet parameters
    Client client;

    // Input fields
    GUI::StaticText enterIPText;
    GUI::TypeField<12> enterIPField;
    GUI::StaticText enterPortText;
    GUI::TypeField<6> enterPortField;
    GUI::TextButton connectButton;
    GUI::TextButton pasteButton;

    void pasteFromClipboard();

    // Main run functions
    void inputMouseDown(App& app) override;
    void inputMouseUp(App& app) override;
    void inputKeys(App& app, SDL_Keycode key) override;
    void inputText(App& app, const char* text) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ClientLobby(App& app);
};
