#pragma once

#include <thread>
#include <mutex>

#include "baseInternet.hpp"
#include "../../cycleTemplate.hpp"


// Class for create process thread for internet connection
class InternetCycle : public Internet, public virtual CycleTemplate
{
protected:
    std::thread gettingCycle{this->lauchCycle, this};  // Thread with running internet connection
    std::mutex gettingMutex;                          // Mutex for control workflow

private:
    void lauchCycle();  // Main internet cycle
public:
    InternetCycle();
    ~InternetCycle();
};
