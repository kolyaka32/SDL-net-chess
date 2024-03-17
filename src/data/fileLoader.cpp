#include "../define.hpp"
#include "dataLoader.hpp"
#include "../workCodes.hpp"


// Loading data from file system (for testing)
#if !ARCHIEVE_LOADING


// Opening archive not needed
DataLoader::DataLoader(){}

// Closing archieve not needed
void DataLoader::closeLoader(){}

//
SDL_RWops *DataLoader::loadObject(const char *_name){
    // Openning need file
    SDL_RWops *tempRW = SDL_RWFromFile(_name, "r");

    // Checking file correction
    #if CHECK_CORRECTION
    if(!tempRW){
        printf("Can't load file '%s'.", _name);
        exit(ERR_FIL_OPN);
    }
    #endif

    // Returning created data structure
    return tempRW;
}

#endif

