/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"
#include "cycleTemplate.hpp"


bool App::running = true;

App::App()
: music{loader, musicFilesNames},
sounds{loader, soundsFilesNames},
initFile(music, sounds),
window{loader} {
    #if CHECK_CORRECTION
    SDL_Log("All loaded and created corretly");
    #endif
}

void App::stop() {
    running = false;
    CycleTemplate::stop();
}

bool App::isRunning() {
    return running;
}
