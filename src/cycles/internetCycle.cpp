/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "internetCycle.hpp"


bool InternetCycle::currentTurn = false;

InternetCycle::InternetCycle(const App& _app)
: GameCycle(_app),
playersTurnsTexts {
    {_app.window, 0.5, 0.1, {"Wait", "Ожидайте", "Erwartet", "Чакаць"}, 24, WHITE},
    {_app.window, 0.5, 0.1, {"Your turn", "Ваш ход", "Sie spielen aus", "Ваш ход"}, 24, WHITE},
},
disconnectedBox(_app.window),
termianatedBox(_app.window) {
    // Resetting flag
    if (!App::isRestarted()) {
        disconnectedBox.reset();
        termianatedBox.reset();
    }
}
