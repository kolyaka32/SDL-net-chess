#include <thread>
#include "data/data.hpp"
#include "GUI/baseGUI.hpp"


//
class SelectCycle
{
private:
    std::thread drawThread{this->drawing, this};  // Thread for drawing
    bool LMBclick;  // Flag of current mouse clicking state
    int mouseX,mouseY;  // Current position of mouse
    Uint8 selectedBox;  // Number of which box is currently selected

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

protected:
    // Data for create own cycle (must be overwriten)
    void getInput();    // Getting all user input (keyboard, mouse...)
    void mouseInput();  // Checking for any need mouse action
    void drawing();     // Drawing all needed objects
public:
    SelectCycle();
    ~SelectCycle();
    void run();         // Start cycle
};
