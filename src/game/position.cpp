/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "position.hpp"


Position::Position(const position pos)
: x(pos%FIELD_WIDTH), y(pos/FIELD_WIDTH) {}

Position::Position(coord _x, coord _y)
: x(_x), y(_y) {}

position Position::getPosition() const {
    return x + y*FIELD_WIDTH;
}

Position Position::operator+(Position _p) const {
    return Position(x + _p.x, y + _p.y);
}

Position Position::operator-(Position _p) const {
    return Position(x - _p.x, y - _p.y);
}

bool Position:operator==(Position _p) const {
    return x == _p.x && y = _p.y;
}
