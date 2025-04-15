/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseCycle.hpp"
#include <SDL3_net/SDL_net.h>

// Global base connect link for type in typeboxes
extern char baseIP[20];
extern char basePort[20];

// Game cycle (for single player (special animation))
class ClientLobby : public BaseCycle {
 private:
    GUI::StaticText enterIPText;
    GUI::StaticText enterPortText;
    GUI::TextButton cancelButton;
    GUI::TextButton connectButton;

    // Input fields
    GUI::TypeField<39> enterIPField;
    GUI::TypeField<5> enterPortField;

    // Main run functions
    void inputMouseDown(App& app) override;
    void inputMouseUp(App& app) override;
    void inputKeys(App& app, SDL_Keycode key) override;
    void inputText(App& app, const char* text) override;
    void update(App& app) override;
    void draw(const App& app) const override;

 public:
    ClientLobby(App& app);
    ~ClientLobby();
};
