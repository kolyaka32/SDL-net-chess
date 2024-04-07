#include "cycleTemplate.hpp"
#include "GUI/baseGUI.hpp"


// Cycle for select variants to start
class SelectCycle : public CycleTemplate
{
private:
    // Counter of start variants
    const static Uint8 optionsCount = 4;

    // Buttons for start variants
    GUI::TextButton startOptions[optionsCount] = {
        {0.5, 0.3, data.texts[TXT_SELECT_SINGLE]},
        {0.5, 0.5, data.texts[TXT_SELECT_TWO]},
        {0.5, 0.7, data.texts[TXT_SELECT_SERVER]},
        {0.5, 0.9, data.texts[TXT_SELECT_CLIENT]},
    };
    
    // Setting menu button
    GUI::ImageButton settingButton{0.95, 0.05, IMG_GUI_PAUSE_BUTTON};

    // New overrided cycle functions
    //void getInput() override;     // Getting all user input (keyboard, mouse...)
    Uint8 mouseInput() override;    // Checking for any need mouse action
    void draw() const override;     // Drawing all needed objects
public:
    SelectCycle();   // Create selecting cycle
    ~SelectCycle();  // Close selecting cycle
};
