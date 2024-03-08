#include "include.hpp"
#include "graphics.hpp"
#include "dataLoader.hpp"

// Names of sound effects in array to use
enum ANI_names{

};

#define ANI_count 0

#if ANI_count
//
class Animations : virtual GraphicsLibrary, public virtual DataLoader
{
private:
    void loadAnimation(const char *name, ANI_names index);
    bool checkCorrection();
protected:
    IMG_Animation *animations[ANI_count];
public:
    Animations();
    ~Animations();
};
#endif
