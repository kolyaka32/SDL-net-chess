#include "include.hpp"

// Names of sound effects in array to use
enum SND_names{

};
#define SND_count 0

class Sounds
{
private:
    Mix_Chunk* sounds[SND_count];  // Array of all sound effects
public:
    Sounds();
    ~Sounds();
    void playSound(SND_names track);
};
