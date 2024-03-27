#include "cycleTemplate.hpp"
#include "GUI/baseGUI.hpp"

//
class SelectCycle : public CycleTemplate
{
private:
    // Interactable part:
    // Buttons for start variants
    const static Uint8 optionsCount = 4;
    GUI::TextButton startOptions[optionsCount] = {
        {0.5, 0.3, data.texts[TXT_SELECT_SINGLE]},
        {0.5, 0.5, data.texts[TXT_SELECT_TWO]},
        {0.5, 0.7, data.texts[TXT_SELECT_SERVER]},
        {0.5, 0.9, data.texts[TXT_SELECT_CLIENT]},
    };
    // Setting menu
    GUI::ImageButton settingButton{0.9, 0.1, IMG_GUI_PAUSE_BUTTON};

    // New overrided cycle functions
    //void getInput() override;    // Getting all user input (keyboard, mouse...)
    Uint8 mouseInput() override;   // Checking for any need mouse action
    void draw() const override;     // Drawing all needed objects
public:
    SelectCycle();
    ~SelectCycle();
};
