#pragma once

#include "base.hpp"
#include "internet/internetServer.hpp"

//
class ServerGameCycle : public GameCycle, public InternetServerCycle
{
private:
    Uint8 getData() override;
public:
    ServerGameCycle();
    ~ServerGameCycle();
};
