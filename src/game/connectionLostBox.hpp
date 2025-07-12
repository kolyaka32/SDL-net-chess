/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"


// Class with message box, showing information at center of screen
class ConnectionLostBox {
private:
    // Flag of activity
    static bool active;

    // Main text
    const GUI::HighlightedStaticText mainText;
    // Button for try to recconect
    const GUI::TextButton reconnectButton;
    // Button for return to menu
    const GUI::TextButton closeButton;
    // Background plate for better visability
    const GUI::Backplate background;

public:
    ConnectionLostBox(const Window& target);
    int click(const Mouse mouse);  // Return non zero, if active, 2 if try to reconnect
    void blit(const Window& target) const;
    static void activate();
    static void reset();
};
