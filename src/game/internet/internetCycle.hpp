#pragma once

#include <thread>
#include <mutex>

#include "baseInternet.hpp"
#include "../../cycleTemplate.hpp"


// Class for create process thread for internet connection
class InternetCycle : public Internet, public virtual CycleTemplate
{
private:
    void lauchCycle();  // Main internet cycle

protected:
    std::thread gettingCycle{this->lauchCycle, this};  // Thread with running internet connection
    std::mutex gettingMutex;                          // Mutex for control workflow

    virtual void initConnection();  // Action, launch after connection

public:
    InternetCycle();
    ~InternetCycle();
};
