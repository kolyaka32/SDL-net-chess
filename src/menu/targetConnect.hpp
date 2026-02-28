/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Menu for target connect at specified address
class TargetConnect {
 protected:
    static bool active;
    static char baseIP[15];
    static char basePort[6];

    // Input fields
    GUI::RoundedBackplate backplate;
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
    void activate();
    void reset();
    bool click(const Mouse mouse);
    void unclick();
    void press(SDL_Keycode key);
    void write(const char* text);
    void update();
    void blit() const;

    // Static functions
    static void writeBaseIP(const char* text);
    static const char* getBaseIP();
    static void writeBasePort(const char* text);
    static const char* getBasePort();
};
