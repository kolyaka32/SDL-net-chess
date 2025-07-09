/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "messageBox.hpp"


int MessageBox::currentIndex = 0;

MessageBox::MessageBox(const Window& _target, const LanguagedText _text, int _boxIndex)
: mainText(_target, 0.5, 0.45, _text, 2, 40, WHITE),
closeButton(_target, 0.5, 0.55, {"Close", "Закрыть", "Schließen", "Зачыніць"}, 24, WHITE),
background(_target, 0.5, 0.5, 0.82, 0.2, 20, 4),
index(_boxIndex) {}

bool MessageBox::click(const Mouse _mouse) {
    if (closeButton.in(_mouse)) {
        currentIndex = 0;
    }
    // Blocking other actions, while box open
    return currentIndex == index;
}

void MessageBox::blit(const Window& _target) const {
    if (index == currentIndex) {
        background.blit(_target);
        closeButton.blit(_target);
        mainText.blit(_target);
    }
}

void MessageBox::activate() {
    currentIndex = index;
}

void MessageBox::activate(int _number) {
    currentIndex = _number;
}
