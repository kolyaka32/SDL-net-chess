#pragma once

#include "cycleTemplate.hpp"
#include "GUI/baseGUI.hpp"


// Cycle for select variants to start
class SelectCycle : public CycleTemplate {
 private:
    // Setting menu button
    GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};

    // New overrided cycle functions
    Uint8 mouseInput() override;    // Checking for any need mouse action
    void draw() const override;     // Drawing all needed objects
 public:
    SelectCycle();   // Create selecting cycle
};
