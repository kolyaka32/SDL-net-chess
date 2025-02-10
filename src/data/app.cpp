/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "app.hpp"


App::App()
 : window{loader},
 music{loader},
 sounds{loader}
{
    // Running current application
    run();
}

App::~App() {

}

void App::run() {

}