/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


// Tempate function for resetting texture
GUI::Template::Template(const Window& _window)
: window(_window) {}

// Template function for draw
void GUI::Template::blit() const {}
