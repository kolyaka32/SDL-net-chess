#pragma once

#include "base.hpp"
#include "internet/internetClient.hpp"

//
class ClientGameCycle : public InternetClientCycle
{
private:
    bool waitStart = true;     // Flag of waiting for game start
    bool waitTurn = true;      // Flag of waiting for another player for turn
    timer lastTypeBoxUpdate;   // Timer for change symbol of caret

    Uint8 getData() override;  //
    void removeSelection();    //

    // Input fields
    GUI::typeBox typeBoxes[2]{
        {runMutex, 20, 0.5, 0.2, data.baseIP.std::string::c_str()},
        {runMutex, 20, 0.5, 0.5, data.basePort.std::string::c_str()}
    };

protected:
    // New overrided cycle functions
    void getInput() override;     // Getting all user input (keyboard, mouse...)
    Uint8 mouseInput() override;  // Checking for any need mouse action
    void draw() const override;   // Drawing all needed objects

public:
    ClientGameCycle();
    ~ClientGameCycle();
};
