/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "data/app.hpp"


// Main function
int main(int argv, char **args) {
    // Creating main window
    Window window{WINDOW_WIDTH, WINDOW_HEIGHT,
        {"Chess on SDL", "Шахматы на SDL", "Schach на SDL", "Шахматы на SDL"}};

    // Running menu
    App::run(window);

    // Successful end of program
    return 0;
}
