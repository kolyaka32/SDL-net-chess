#pragma once

#include <thread>
#include <mutex>

#include "baseInternet.hpp"
#include "../base.hpp"
#include "../../data/idleTimer.hpp"


// Class for create process thread for internet connection
class InternetCycle : public Internet, public GameCycle
{
 private:
    IdleTimer internetTimer{1000/INTERNET_FPS};  // Timer to idle in internet cycle
    void lauchCycle();  // Main internet cycle for side thread

 protected:
    std::thread gettingCycle{this->lauchCycle, this};  // Thread with running internet connection
    std::mutex gettingMutex;                          // Mutex for control workflow

 public:
    InternetCycle();
    ~InternetCycle();
};
