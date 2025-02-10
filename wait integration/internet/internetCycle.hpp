/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "baseInternet.hpp"
#include "../../cycles/gameCycle.hpp"
#include "../../data/idleTimer.hpp"


// Class for create process thread for internet connection
class InternetCycle : public Internet, public GameCycle {
 private:
    void updateInternet();  // Update all internet data

 public:
    InternetCycle();

    // Main cycle function (special for internet use)
    void run() override;
};
