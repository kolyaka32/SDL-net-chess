/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "savedFields.hpp"


std::vector<Field> SavedFields::startOptions{};
bool SavedFields::active = false;

SavedFields::SavedFields(const Window& _window)
: Template(_window),
backplate(_window, 0.5, 0.51, 0.94, 0.8, 20.0, 4.0),
scroller(_window, 0.5, 0.51, 0.94, 0.8, 3, startOptions, {"No saves", "Нет сохранений", "Keine Speicherung", "Няма захаванняў"}),
exitButton(_window, 0.5, 0.81, {"Close", "Закрыть", "Schließen", "Зачыніць"}) {}

void SavedFields::activate() {
    active = true;
}

bool SavedFields::isActive() {
    return active;
}

void SavedFields::reset() {
    active = false;
}

const Field* SavedFields::click(const Mouse _mouse) {
    if (exitButton.in(_mouse)) {
        active = false;
        return nullptr;
    }
    if (int i = scroller.click(_mouse)) {
        active = false;
        return &startOptions[i-1];
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
    if (active && backplate.in(mouse)) {
        scroller.scroll(mouse, _wheelY);
    }
}

void SavedFields::blit() const {
    if (active) {
        backplate.blit();
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
    // Check on size (has need byte of size and fit correctly)
    if (_saveText.size() > 4 && _saveText.size() == Field::getSaveSize(_saveText[1]-'0')) {
        // Create field
        startOptions.emplace_back(_saveText.c_str());
        // Check control sum
        if (startOptions[startOptions.size()-1].getCheckSum() != _saveText[0]) {
            startOptions.pop_back();
            return;
        }
        // Adding to counter
        /*if (endField >= maxFieldNumber) {
            startField++;
        }
        endField++;*/
    }
}

void SavedFields::saveFields(std::ofstream& _fout) {
    for (auto f : startOptions) {
        _fout << "save = ";
        const Array<char> save = f.getSave();
        _fout.write(save.getData(), save.getSize());
        _fout << '\n';
    }
}
