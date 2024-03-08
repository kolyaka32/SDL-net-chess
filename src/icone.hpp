#pragma once

#include "include.hpp"
#include "graphics.hpp"
#include "dataLoader.hpp"


//
class Icone : virtual GraphicsLibrary, public virtual DataLoader
{
private:
    /* data */
public:
    Icone();
    ~Icone();

    bool loadIcone(const char *name);
};
