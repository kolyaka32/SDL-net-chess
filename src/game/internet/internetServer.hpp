#pragma once

#include "internetCycle.hpp"


// Class of game server
class InternetServerCycle : public InternetCycle
{
protected:
    Uint16 serverPort = BASE_PORT;  // Port, where server was created
public:
    InternetServerCycle();
    ~InternetServerCycle();
};
