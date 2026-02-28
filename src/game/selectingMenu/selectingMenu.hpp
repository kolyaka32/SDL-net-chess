/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "startFields.hpp"
#include "savedFields.hpp"


// Options for start new game (new or saved)
class SelectingMenu {
 private:
    static bool active;

    StartFields startFields;
    SavedFields savedFields;

    // Menu after game end
    GUI::RoundedBackplate backplate;
    GUI::TextButton continueButton;
    GUI::TextButton startNewButton;
    GUI::TextButton loadButton;
    GUI::TextButton exitButton;

 public:
    explicit SelectingMenu(const Window& window);
    void activate();
    static void reset();
    static void open();
    static bool isActive();
    void addField(const Field& field);
    const Field* click(const Mouse mouse);
    void unclick();
    void update();
    void scroll(float wheelY);
    void escape();
    void blit() const;
};
