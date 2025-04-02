/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "cycleTemplate.hpp"

App::App()
: music{loader},
sounds{loader},
initFile(music, sounds),
window{loader} {}

App::~App() {}

void App::stop() {
    running = false;
}

void App::startNextCycle(CYCLE_types _type) {
    nextCycle = _type;
}
