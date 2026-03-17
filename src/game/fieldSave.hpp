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

 protected:
    // Getting check sum
    char getCheckSum() const;

 public:
    // Create from excisting field (current)
    FieldSave(const Field& field);
    // Create from save file (straight)
    FieldSave(const char* save, int length);

    // Functions for show create information
    const char* getSaveTime() const;  // Getting field create time
    // const char* getName() const;   // Getting field name
    void blit(const Window& window) const;  // Special blitting for draw icone

    // Save system
    const char* getSave() const;
    // Check correction of created field
    bool isCorrect(char checksum) const;
};

// Basic start field
extern const char* basicStartString;
extern FieldSave basicStartField;
