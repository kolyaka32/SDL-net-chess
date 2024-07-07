/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "data/data.hpp"
#include "cycles/selectCycle.hpp"

// Main process data
Data data;

// Declaration of global 
GUI::ImageButton BaseCycle::exitButton{0.05, 0.05, IMG_GUI_QUIT_BUTTON};
SettingsMenu BaseCycle::settings;

// Main function
int main(int argv, char **args) {
    // Starting selecting cycle
    SelectCycle cycle;

    // Running selecting cycle
    cycle.run();

    // Reloading game if need
    if (data.restart) {
        data.restart = false;
        return main(argv, args);
    }

    // Successful end of program
    return 0;
}
