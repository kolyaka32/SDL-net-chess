#include <thread>
#include "data/data.hpp"


//
class CycleTemplate
{
private:
    std::thread drawThread{this->drawing, this};  // Thread for drawing
    

protected:
    // Data for cycle
    //bool LMBclick;  // Flag of current mouse clicking state
    int mouseX, mouseY;  // Current position of mouse
    Uint8 selectedBox;  // Number of which box is currently selected

    // Cycle functions for own cycle (must be overriden)
    virtual void getInput();    // Getting all user input (keyboard, mouse...)
    virtual void mouseInput();  // Checking for any need mouse action
    virtual void drawing();     // Drawing all needed objects
public:
    CycleTemplate();
    ~CycleTemplate();
    void run();         // Start cycle
};
