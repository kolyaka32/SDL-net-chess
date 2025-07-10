/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Class with message box, showing information at center of screen
class MessageBox {
private:
    // System for acivate need box globaly
    static int currentIndex;  // Index of currently selected box for showing
    const int index;          // Index of current box

    // Main text
    const GUI::HighlightedStaticText mainText;
    // Button for close this box
    const GUI::TextButton closeButton;
    // Background plate for better visability
    const GUI::Backplate background;

public:
    MessageBox(const Window& target, const LanguagedText text, int boxIndex);
    bool click(const Mouse mouse);
    void blit(const Window& target) const;
    void activate();
    static void activate(int number);
};
