#pragma once

#include "SDL_rwops.h"


// Class of readable/writable data structure
class RWops
{
private:
    SDL_RWops* data;
public:
    RWops(/* args */);
    RWops(RWops& _rwops);
    ~RWops();
};
