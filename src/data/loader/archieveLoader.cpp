/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "archieveLoader.hpp"
#include "../../define.hpp"

ArchieveLoader::ArchieveLoader() {
    // Open archive with need name
    archive = zip_open(DATA_FILE, ZIP_RDONLY, NULL);

    #if ARCHIEVE_PASSWORD
    zip_set_default_password(archive, ARCHIEVE_PASSWORD);
    #endif

    // Checking openning correction
    #if CHECK_CORRECTION
    if (!archive) {
        throw DataLoadException("load archieve: " + std::string(DATA_FILE));
    }
    #endif
}

ArchieveLoader::~ArchieveLoader() {
    zip_close(archive);
}

SDL_IOStream* ArchieveLoader::load(const char* _file) const {
    // Openning need file
    zip_file_t *file = zip_fopen_encrypted(archive, _file, 0, ARCHIEVE_PASSWORD);

    // Checking correction of openned file
    #if CHECK_CORRECTION
    if (file == nullptr) {
        throw DataLoadException("load file from archieve: " + std::string(_file));
    }
    #endif

    // Getting states of need file
    zip_stat_t st;
    zip_stat(archive, _file, 0, &st);

    // Checking correction of openned file
    #if CHECK_CORRECTION
    if (st.size == 0) {
        throw DataLoadException("load file from archieve: " + std::string(_file));
    }
    #endif

    // Creating buffer for data
    Uint8* buffer = new Uint8[st.size];

    // Copping data to buffer
    zip_fread(file, buffer, st.size);

    // Closing readed file
    zip_fclose(file);

    // Creating SDL-based structure with this data
    SDL_IOStream *tempIO = SDL_IOFromConstMem(buffer, st.size);

    // Checking correction of loaded object
    #if CHECK_CORRECTION
    if (!tempIO) {
        throw DataLoadException("load file from archieve: " + std::string(_file));
    }
    #endif

    // Returning created data structure
    return tempIO;
}
