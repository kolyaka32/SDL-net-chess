/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "terminatedBox.hpp"
#include "../data/cycleTemplate.hpp"


bool TerminatedBox::active = false;

TerminatedBox::TerminatedBox(const Window& _target)
: mainText(_target, 0.5, 0.45, {"Connection terminated", "Соединение разорвано", "Verbindung unterbrochen", "Злучэнне разарвана"}, 2, 40, WHITE),
closeButton(_target, 0.5, 0.55, {"Close", "Закрыть", "Schließen", "Зачыніць"}, 24, WHITE),
background(_target, 0.5, 0.5, 0.82, 0.2, 20, 4) {}

bool TerminatedBox::click(const Mouse _mouse) {
    if (active) {
        // Returning to menu
        if (closeButton.in(_mouse)) {
            CycleTemplate::stop();
        }
        // Blocking other actions, while box open
        return true;
    }
    return false;
}

void TerminatedBox::blit(const Window& _target) const {
    if (active) {
        background.blit(_target);
        closeButton.blit(_target);
        mainText.blit(_target);
    }
}

void TerminatedBox::activate() {
    active = true;
}

void TerminatedBox::reset() {
    active = false;
}

bool TerminatedBox::isActive() {
    return active;
}
