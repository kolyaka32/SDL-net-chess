
#include "include.hpp"

// Names of all music tracks
enum MUS_names{

};

#define MUS_count 0

class Musics
{
private:
    Mix_Music* musics[MUS_count];      // Array of all music
    SDL_RWops* musicsData[MUS_count];  // Array of data for music
public:
    Musics();
    ~Musics();
    //Mix_Music* operator[](MUS_names num);
    void startPlay(unsigned num);
};
