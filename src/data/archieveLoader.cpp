#include "zip.h"
#include "../define.hpp"
#include "dataLoader.hpp"
#include "../workCodes.hpp"


// Functions for loading data from archieve
#if ARCHIEVE_LOADING

// Archive with all data
static zip_t* archive;  


// Openning archieve
DataLoader::DataLoader(){
    // Open archive with need name
    archive = zip_open(DATA_FILE, ZIP_RDONLY, NULL);

    #if ARCHIEVE_PASSWORD
    zip_set_default_password(archive, ARCHIEVE_PASSWORD);
    #endif

    // Checking openning correction
    #if CHECK_CORRECTION
    if(!archive){
        printf("Can't load archieve '%s'.", DATA_FILE);
        exit(ERR_FIL_OPN);
    }
    #endif
}

// Closing archive
void DataLoader::closeLoader(){
    zip_close(archive);
}

// Loading object with need name
SDL_RWops *DataLoader::loadObject(const char *_name){
    // Openning need file
    zip_file_t *file = zip_fopen_encrypted(archive, _name, 0, ARCHIEVE_PASSWORD);
    
    // Getting states of need file
    zip_stat_t st;
	zip_stat(archive, _name, 0, &st);

    // Checking correction of openned file
    #if CHECK_CORRECTION
    if(st.size == 0){
        return nullptr;
    }
    #endif

    // Creating buffer for data
    char *buffer = (char*)malloc(sizeof(char) * st.size);

    // Copping data to buffer
    zip_fread(file, buffer, st.size);

    // Closing readed file
    zip_fclose(file);

    // Creating SDL-based structure with this data
    SDL_RWops *tempRW = SDL_RWFromMem(buffer, st.size);

    // Checking correction of loaded object
    #if CHECK_CORRECTION
    if(!tempRW){
        printf("Can't load object '%s' from arhieve", _name);
        exit(ERR_FIL_OPN);
    }
    #endif

    // Returning created data structure
    return tempRW;
}
#endif
