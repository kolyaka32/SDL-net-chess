#pragma once

#include "base.hpp"
#include "internet/internetClient.hpp"

//
class ClientGameCycle : public GameCycle, public InternetClientCycle
{
private:
    Uint8 getData() override;
public:
    ClientGameCycle();
    ~ClientGameCycle();
};
