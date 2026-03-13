/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "field.hpp"


// Class with field save with additional data for loadding (time, name)
class FieldSave : public Field {
 private:
    // Data for save/load
    SDL_Time saveTime;

 public:
    // Create from excisting field (current)
    FieldSave(const Field& field);
    // Create from save file (straight)
    FieldSave(const char* save);

    // Functions for show load information
    const char* getSaveTime() const;  // Getting field create time
    // const char* getName() const;   // Getting field name

    // Save system
    const char* getSave() const;
    char getCheckSum() const;
};
