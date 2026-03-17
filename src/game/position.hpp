/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../data/app.hpp"


// Type for storing one-dimanional position (or offset)
typedef Sint8 coord;
// Type for storing two-dimansinal position
typedef Uint8 position;

// Class with 2-dimansional position and it conversion
class Position {
 public:
    // Local position
    coord x, y;

 public:
    // Conversion options
    Position(const position pos);
    Position(coord x, coord y);
    position getPosition() const;

    // Math options
    Position operator+(const Position p) const;
    Position operator-(const Position p) const;
    bool operator==(const Position p) const;
};
