#pragma once

#include "dataLoader.hpp"


// Class of simplier implimintation of loading file, straight from file
class StraightLoader : public DataLoader
{
private:
    /* data */
public:
    StraightLoader(/* args */);
    ~StraightLoader() override;
    SDL_IOStream* load(const char* name) override;
};
