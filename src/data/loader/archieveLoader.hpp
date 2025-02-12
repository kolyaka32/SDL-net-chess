#pragma once

#include "dataLoader.hpp"


// Implimentation of loader for arcives
class ArchieveLoader : public DataLoader
{
private:
    /* data */
public:
    ArchieveLoader(/* args */);
    ~ArchieveLoader() override;
    SDL_IOStream* load(const char* name) const override;
};
