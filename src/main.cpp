/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"
#include "game/gameField.hpp"  // Get window width and height


// Main function
int main(int argv, char **args) {
    // Creating main window
    Window window{GameField::getWindowWidth(), GameField::getWindowHeight(),
        {"Tic-tac-toe", "Крестики нолики", "Tic-tac-toe", "Крыжыкі нулікі"}};

    // Running menu
    App::run(window);

    // Successful end of program
    return 0;
}
