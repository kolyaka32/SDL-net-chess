/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "startFields.hpp"


Field StartFields::startOptions[4] = {
    {3, 3},
    {5, 4},
    {7, 5},
    {9, 7},
};
bool StartFields::active = false;

StartFields::StartFields(const Window& _window)
: backplate{_window, 0.5, 0.5, 0.7, 0.7, 20, 4},
optionButton {
    {_window, 0.5, 0.24, {"Small field", "Маленькое поле", "Kleines Feld", "Невялікае поле"}},
    {_window, 0.5, 0.36, {"Medium field", "Среднее поле", "Mittleres Feld", "Сярэдняе поле"}},
    {_window, 0.5, 0.48, {"Big field", "Большое поле", "Großes Feld", "Вялікае поле"}},
    {_window, 0.5, 0.6, {"Huge field", "Огромное поле", "Riesiges Feld", "Вялікае поле"}},
},
closeButton{_window, 0.5, 0.75, {"Close", "Закрыть", "Schließen", "Зачыніць"}} {}

void StartFields::activate() {
    active = true;
}

bool StartFields::isActive() {
    return active;
}

void StartFields::reset() {
    active = false;
}

const Field* StartFields::click(const Mouse _mouse) {
    if (closeButton.in(_mouse)) {
        active = false;
        return nullptr;
    }
    for (int i=0; i < 4; ++i) {
        if (optionButton[i].in(_mouse)) {
            // Making sound
            audio.sounds.play(Sounds::Reset);
            audio.music.startFromCurrent(Music::MainCalm);
            // Setting new field
            active = false;
            return startOptions + i;
        }
    }
    return nullptr;
}

void StartFields::blit() const {
    if (active) {
        backplate.blit();
        for (int i=0; i < 4; ++i) {
            optionButton[i].blit();
        }
        closeButton.blit();
    }
}
