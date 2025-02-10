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
    RWops* load(const char* name) override;
};
