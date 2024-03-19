#pragma once

#include "graphics.hpp"
#include "dataLoader.hpp"


//
class Icone : virtual GraphicsLibrary, public virtual DataLoader
{
private:
    bool loadIcone(const char *name);
public:
    Icone();
    ~Icone();
};
