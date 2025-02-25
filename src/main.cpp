/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"

// Global application data
App application;

// Main function
int main(int argv, char **args) {
    // Running selected app
    application.run();

    // Reloading game if need
    /*if (data.restart) {
        data.restart = false;
        return main(argv, args);
    }*/

    // Successful end of program
    return 0;
}
