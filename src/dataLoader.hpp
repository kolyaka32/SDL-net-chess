#pragma once

#include "include.hpp"
#include "application.hpp"


// 
#define ARCHIEVE_PASSWORD NULL


// 
class DataLoader : public virtual App
{
protected:
    SDL_RWops *loadObject(const char *name);
public:
    DataLoader();
    ~DataLoader();

    void closeLoader();
};
