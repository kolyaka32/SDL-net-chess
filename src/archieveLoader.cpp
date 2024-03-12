#include "include.hpp"
#include "zip.h"
#include "define.hpp"
#include "dataLoader.hpp"
#include "workCodes.hpp"


// Functions of loading need outside data
#if ARCHIEVE_LOADING
// Functions for loading data from archieve
// Loading need library


// Arcieve local structs
static zip_t* archive;  // Archive with all data



//
DataLoader::DataLoader(){
    // Open archive with need name
    archive = zip_open(DATA_FILE, ZIP_RDONLY, NULL);

    #if ARCHIEVE_PASSWORD
    zip_set_default_password(archive, ARCHIEVE_PASSWORD);
    #endif

    // Checking openning correction
    if(!archive){
        printf("Can't load archieve '%s'.", DATA_FILE);
        exit(ERR_FIL_OPN);
    }
}

//
DataLoader::~DataLoader(){

}

//
void DataLoader::closeLoader(){
    // Closing archive
    zip_close(archive);
}

//
SDL_RWops *DataLoader::loadObject(const char *_name){
    // Openning need file
    zip_file_t *file = zip_fopen_encrypted(archive, _name, 0, ARCHIEVE_PASSWORD);
    
    // Getting states of need file
    zip_stat_t st;
	zip_stat(archive, _name, 0, &st);

    // Checking correction of openned file
    if(st.size == 0){
        return nullptr;
    }

    // Creating buffer for data
    char *buffer = (char*)malloc(sizeof(char) * st.size);

    // Copping data to buffer
    zip_fread(file, buffer, st.size);

    // Closing readed file
    zip_fclose(file);

    // Creating SDL-based structure with this data
    SDL_RWops *tempRW = SDL_RWFromMem(buffer, st.size);

    // Checking correction of loaded object
    if(!tempRW){
        printf("Can't load object '%s' from arhieve", _name);
        exit(ERR_FIL_OPN);
    }

    // Returning created data structure
    return tempRW;
}
#endif
