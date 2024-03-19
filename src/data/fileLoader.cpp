#include "../define.hpp"
#include "dataLoader.hpp"
#include "../workCodes.hpp"


// Trying loading data from folder (for testing)
#if !ARCHIEVE_LOADING

DataLoader::DataLoader(){
    // Open archive not needed
}

//
DataLoader::~DataLoader(){

}

//
void DataLoader::closeLoader(){
    // Closing archieve not needed
}

//
SDL_RWops *DataLoader::loadObject(const char *_name){
    // Openning need file
    SDL_RWops *tempRW = SDL_RWFromFile(_name, "r");

    // Checking file correction
    if(!tempRW){
        printf("Can't load file '%s'.", _name);
        exit(ERR_FIL_OPN);
    }

    // Returning created data structure
    return tempRW;
}

#endif

