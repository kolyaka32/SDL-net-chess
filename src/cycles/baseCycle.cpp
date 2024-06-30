#include "baseCycle.hpp"

// Base cycle class
BaseCycle::BaseCycle(MUS_names _music) : music(_music) {
    // Resetting values
    selectedBox = 0;

    // Starting playing need music
    if (music) {
        data.playMusic(music);
    }
}
