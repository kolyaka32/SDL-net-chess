#pragma once

#include "graphics.hpp"
#include "dataLoader.hpp"


// Total animation counter
#define ANI_count 0

// Data for work with animations
#if ANI_count

// Names of sound effects in array to use
enum ANI_names{

};

// Base class with all animations
class Animations : virtual GraphicsLibrary, public virtual DataLoader {
 protected:
    IMG_Animation *animations[ANI_count];  // List with all animations

 private:
    // Function for load animation with need name
    void loadAnimation(const char *name, ANI_names index);
    // Check, if all animations load correctly (if need)
    #if CHECK_CORRECTION
    void checkCorrection();
    #endif

 public:
    Animations();
    ~Animations();
};
#endif
