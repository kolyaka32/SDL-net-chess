/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "../cycles/selectCycle.hpp"

// Global application data
App application;

// Main function
int main(int argv, char **args) {
    // Running menu
    CycleTemplate::runCycle<SelectCycle>(application);

    // Successful end of program
    return 0;
}
