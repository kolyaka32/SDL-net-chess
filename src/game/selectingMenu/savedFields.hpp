/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <fstream>
#include <vector>
#include "saveInfo.hpp"


// Class for store all game saves and load it, when need
class SavedFields : GUI::Template {
 private:
    static std::vector<Field> startOptions;
    static bool active;

    // Draw options
    GUI::RoundedBackplate backplate;
    GUI::ScrollBox<SaveInfo, Field> scroller;
    GUI::TextButton exitButton;

 public:
    explicit SavedFields(const Window& window);
    void activate();
    bool isActive();
    void reset();
    const Field* click(const Mouse mouse);
    void unclick();
    void update();
    void scroll(float wheelY);
    void blit() const override;

    // Work with global saves
    void addFieldRuntime(const Field& field);  // Add another field during runtime
    static void addField(const Field& field);
    static void addField(const std::string saveText);
    static void saveFields(std::ofstream& stream);
};
