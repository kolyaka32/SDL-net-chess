/*
 * Copyright (C) 2024-2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "languages.hpp"
#include "initFile.hpp"
#include "../GUI/baseGUI.hpp"

// Class for updating all GUI objects
class UpdateList {
 private:
    const static Uint8 maxSize = 30;  // Maximal count of updating objects
    Uint8 size = 0;                   // Current size of updating list
    GUI::GUItemplate* languageUpdateList[maxSize];  // List with all updating objects

 public:
    UpdateList();
    void add(GUI::GUItemplate* object);
    void enterCycle();  // Entering internal cycle
    void exitCycle();   // Exiting internal cycle
    void update();      // Updating all entered items
};


// All static texts
class Texts : public virtual App, public virtual InitFile {
 public:
    // Array for update language
    UpdateList updateList;

 public:
    Texts();   // Create and update all static texts
    void updateTranslation();  // Update translations of all texts
    void updateTitle();        // Update window title
};
