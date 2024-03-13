#include "include.hpp"
#include "data.hpp"
#include "GUI/baseGUI.hpp"


class SelectCycle
{
private:
    bool running;  // Flag of running current process
    bool stop;     // Flag of stopping current process for another
    bool LMBclick;  // Flag of current mouse clicking state
    int mouseX,mouseY;  // Current position of mouse
    Uint8 selectedBox;  // Number of which box is currently selected

    // Interactable part:
    // Buttons for start variants
    const static Uint8 optionsCount = 4;
    GUI::TextButton startOptions[optionsCount] = {
        {0.5, 0.1, data.texts[TXT_SELECT_SINGLE]},
        {0.5, 0.2, data.texts[TXT_SELECT_SINGLE]},
        {0.5, 0.3, data.texts[TXT_SELECT_SINGLE]},
        {0.5, 0.4, data.texts[TXT_SELECT_SINGLE]},
    };
    // Setting menu
    GUI::ImageButton settingButton{0.9, 0.1, IMG_GUI_PAUSE_BUTTON};
public:
    SelectCycle();
    ~SelectCycle();
    void getInput();    // Getting all user input (keyboard, mouse...)
    void mouseInput();  // Checking for any need mouse action
    void drawing();     // Drawing all needed objects
    void run();         // Start cycle
};
