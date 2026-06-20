/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <fstream>
#include <vector>
#include "saveInfo.hpp"


// Class for store all game saves and load it, when need
class SavedFields : public GUI::SubWindow {
 private:
    static std::vector<FieldSave> startOptions;

    // Draw options
    GUI::ScrollBox<SaveInfo, FieldSave> scroller;
    GUI::TextButton exitButton;

 public:
    explicit SavedFields(const Window& window);
    const Field* click(const Mouse mouse);
    void unclick();
    void update();
    void scroll(float wheelY);
    void blit() const override;

    // Work with global saves
    void addFieldRuntime(const Field& field);  // Add field during runtime 
    static void addField(const Field& field);
    static void addField(const std::string);
    static void saveFields(std::ofstream& stream);
};
