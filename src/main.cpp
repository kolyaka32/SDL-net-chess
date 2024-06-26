/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "data/data.hpp"
#include "selectCycle.hpp"
#include "workCodes.hpp"

// Main process data
Data data;

// Main function
int main(int argv, char **args) {
    // Starting selecting cycle
    SelectCycle cycle;

    // Running cycle
    cycle.run();

    // Reloading game if need
    if (data.restart) {
        data.restart = false;
        return main(argv, args);
    }

    // Successful end of program
    return 0;
}
