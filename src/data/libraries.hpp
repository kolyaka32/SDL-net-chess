/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <SDL3/SDL_audio.h>

// Class for load and close needed libraries
class Libraries {
private:
    SDL_AudioDeviceID audioDeviceID = 0;
public:
    Libraries();
    ~Libraries() noexcept;
};
