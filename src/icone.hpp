#pragma once

#include "include.hpp"
#include "graphics.hpp"
#include "dataLoader.hpp"


//
class Icone : GraphicsLibrary, public DataLoader
{
private:
    /* data */
public:
    Icone();
    ~Icone();

    bool loadIcone(const char *name);
};
