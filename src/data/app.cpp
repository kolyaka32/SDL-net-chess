/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "cycleTemplate.hpp"


bool App::running = true;

void App::stop() {
    running = false;
    CycleTemplate::stop();
}

bool App::isRunning() {
    return running;
}

void App::setNextCycle(Cycle _nextCycle) {
    nextCycle = _nextCycle;
    CycleTemplate::stop();
}

Cycle App::getNextCycle() {
    return nextCycle;
}
