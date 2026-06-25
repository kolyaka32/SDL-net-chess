/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Menu for target connect at specified address
class TargetConnect : public GUI::SubWindow {
 protected:
    static char baseIP[15];
    static char basePort[6];

    // Input fields
    GUI::StaticText IPText;
    GUI::TypeBox<15> IPField;
    GUI::StaticText portText;
    GUI::TypeBox<6> portField;
    GUI::TextButton pasteButton;
    GUI::TextButton connectButton;
    GUI::TextButton closeButton;

    void pasteFromClipboard();
    void tryConnect();

 public:
    TargetConnect(Window& window);
    bool click(const Mouse mouse);
    void unclick();
    bool press(SDL_Keycode key);
    bool write(const char* text);
    void update();
    void blit() const override;

    // Static functions
    static void writeBaseIP(const char* text);
    static const char* getBaseIP();
    static void writeBasePort(const char* text);
    static const char* getBasePort();
};
