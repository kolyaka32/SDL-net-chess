/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "field.hpp"


// Class with field save with additional data for loadding (time, name)
class FieldSave : Field {
 private:
    // Data for save/load
    SDL_Time saveTime;

 public:
    FieldSave(const Field& field);
    FieldSave(const char* save);

    // Functions for show load information
    const char* getSaveTime() const;  // Getting field create time
    // const char* getName() const;   // Getting field name

    // Save system
    const char* getSave() const;
    char getCheckSum() const;
};
