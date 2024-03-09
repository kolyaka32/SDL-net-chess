#pragma once

#include "data.hpp"

// Main process
class Process : public virtual Data
{
public:
    // Extra data
public:
    Process();  // Initialasing all libraries
    int run();
    ~Process();  // Closing all libraries
};
