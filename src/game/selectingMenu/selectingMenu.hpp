/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "savedFields.hpp"


// Options for start new game (new or saved)
class SelectingMenu : public GUI::SubWindow {
 private:
    // Start options
    SavedFields savedFields;

    // Menu after game end
    GUI::TextButton continueButton;
    GUI::TextButton startNewButton;
    GUI::TextButton loadButton;
    GUI::TextButton exitButton;

 public:
    explicit SelectingMenu(const Window& window);
    void addField(const Field& field);
    bool escape() override;
    const Field* click(const Mouse mouse);
    void unclick();
    void update();
    bool scroll(float wheelY);
    void blit() const;
};
