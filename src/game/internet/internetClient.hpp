#pragma once

#include "internetCycle.hpp"


// Class of game client
class InternetClientCycle : public InternetCycle
{
private:
    
public:
    InternetClientCycle();
    ~InternetClientCycle();

    Uint8 tryConnect(const char* ipText, const char* portText);  // Return 1, if connected
};

