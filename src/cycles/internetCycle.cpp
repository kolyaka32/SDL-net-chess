/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "internetCycle.hpp"


bool InternetCycle::currentTurn = false;

InternetCycle::InternetCycle(Window& _window)
: GameCycle(_window),
currentTurnText(_window, 0.5, 0.05, {"Your turn", "Ваш ход", "Sie spielen aus", "Ваш ход"}),
opponentTurnText(_window, 0.5, 0.05, {"Wait", "Ожидайте", "Erwartet", "Чакаць"}),
disconnectedBox(_window, {"Connection lost", "Соединение потярено", "Verbindung verloren", "Злучэнне страчана"},
    {"Reconnect", "Переприсоединится", "Wiederverbinden", "Паўторна падлучыцца"},
    {"Close", "Закрыть", "Schließen", "Зачыніць"}),
termianatedBox(_window, {"Connection terminated", "Соединение разорвано", "Verbindung unterbrochen", "Злучэнне разарвана"},
    {"Close", "Закрыть", "Schließen", "Зачыніць"}),
looseText(_window, 0.5, 0.05, {"You loose", "Вы проиграли", "Sie haben verloren", "Вы прайгралі"}),
winText(_window, 0.5, 0.05, {"Win", "Победа", "Sieg", "Перамога"}) {
    // Resetting flag
    if (!isRestarted()) {
        disconnectedBox.reset();
        termianatedBox.reset();
    }
    logAdditional("Start internet game cycle");
}

bool InternetCycle::inputMouseDown() {
    if (GameCycle::inputMouseDown()) {
        return true;
    }
    if (int code = termianatedBox.click(mouse)) {
        if (code == 2) {
            // Quiting to menu
            App::setNextCycle(Cycle::Menu);
        }
        // Not allowing to any another actions
        return true;
    }
    if (int code = disconnectedBox.click(mouse)) {
        if (code == 2) {
            // Trying to reconnect
            internet.sendAll({ConnectionCode::ApplyConnection});
        } else if (code == 3) {
            // Going to menu
            App::setNextCycle(Cycle::Menu);
        }
        // Not allowing to any another actions
        return true;
    }
    return false;
}

void InternetCycle::update() {
    // Basic update
    GameCycle::update();
    // Getting messages
    while (const GetPacket* packet = internet.getNewMessages()) {
        getInternetPacket(*packet);
    }
    // Checking applied messages
    internet.checkResendMessages();

    // Appling status
    internet.checkNeedApplyConnection();

    // Checking status
    if (internet.checkStatus()) {
        disconnectedBox.activate();
    } else {
        disconnectedBox.reset();
    }
}

void InternetCycle::getInternetPacket(const GetPacket& packet) {
    switch (ConnectionCode(packet.getData<Uint8>(0))) {
    case ConnectionCode::Quit:
        termianatedBox.activate();
        break;

    default:
        break;
    }
}

