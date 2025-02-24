/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"


// Declaration of global objects
//const GUI::ImageButton BaseCycle::exitButton{0.05, 0.05, IMG_GUI_QUIT_BUTTON};
//SettingsMenu BaseCycle::settings;


// Main function
int main(int argv, char **args) {
    // Main process data
    App app;

    // Running selected app
    app.run();

    // Reloading game if need
    /*if (data.restart) {
        data.restart = false;
        return main(argv, args);
    }*/

    // Successful end of program
    return 0;
}
