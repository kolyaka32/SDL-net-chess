/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "savedFields.hpp"


std::vector<FieldSave> SavedFields::startOptions{};

SavedFields::SavedFields(const Window& _window)
: SubWindow(_window, 0.5, 0.5, 0.94, 0.8),
scroller(_window, 0.52, 0.49, 0.9, 0.68, 3, startOptions,
    {"No saves", "Нет сохранений", "Keine Speicherung", "Няма захаванняў"}),
exitButton(_window, 0.5, 0.86, {"Close", "Закрыть", "Schließen", "Зачыніць"}) {}

const Field* SavedFields::click(const Mouse _mouse) {
    if (exitButton.in(_mouse)) {
        close();
        return nullptr;
    }
    if (int i = scroller.click(_mouse)) {
        if (i >= GUI::Button1) {
            close();
            return &startOptions[i-GUI::Button1];
        }
    }
    return nullptr;
}

void SavedFields::unclick() {
    scroller.unclick();
}

void SavedFields::update() {
    if (active) {
        Mouse mouse;
        mouse.updatePos();
        scroller.update(mouse);
    }
}

void SavedFields::scroll(float _wheelY) {
    Mouse mouse{};
    mouse.updatePos();
    if (active && background.in(mouse)) {
        scroller.scroll(mouse, _wheelY);
    }
}

void SavedFields::blit() const {
    if (active) {
        background.blit();
        scroller.blit();
        exitButton.blit();
    }
}

void SavedFields::addFieldRuntime(const Field& _field) {
    // Add to global list
    addField(_field);

    // Check, if add, when has place
    scroller.addItem(_field);
}


// Static objects
void SavedFields::addField(const Field& _field) {
    startOptions.push_back(_field);
}

void SavedFields::addField(const std::string _saveText) {
    // Creating object
    const FieldSave save{_saveText.c_str(), (int)_saveText.size()};
    // Check if field correct
    if (save.isCorrect(_saveText[0])) {
        // Add this field
        startOptions.push_back(save);
    }
}

void SavedFields::saveFields(std::ofstream& _fout) {
    for (auto f : startOptions) {
        _fout << "save = ";
        _fout << f.getSave();
        _fout << '\n';
    }
}
