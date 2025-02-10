#pragma once

#include "rwops.hpp"



// Interface for load file
class DataLoader {
private:
    /* data */
public:
    DataLoader(/* args */);
    virtual ~DataLoader();
    virtual RWops* load(const char* file);
};
