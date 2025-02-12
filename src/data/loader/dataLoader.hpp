#pragma once

#include <SDL3/SDL_iostream.h>


// Interface for load file
class DataLoader {
private:
    /* data */
public:
    DataLoader(/* args */);
    virtual ~DataLoader();
    virtual SDL_IOStream* load(const char* file) const;
};
