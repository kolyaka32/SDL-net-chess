/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "field.hpp"


Field::Field() {
    // Firstly resetting all figures
    resetField();
}

Field::Field(const Field& _field)
: state(_field.state),
castling(_field.castling),
wasMoven(_field.wasMoven) {
    memcpy(figures, _field.figures, sizeof(figures));
}

void Field::resetField() {
    // Clearing data
    // Resetting all field
    memset(figures, FIG_NONE, sqr(FIELD_WIDTH));
    // First move from white figures
    state = GameState::CurrentPlay;
    // Flag of checking, if was turn
    wasMoven = false;
    // Resetting all castlings - not possible
    castling = 0;
}

bool Field::isAttackable(position _pos) {
    cell c = figures[_pos];
    if (state == GameState::CurrentPlay) {
        // White turn
        return (c >= FIG_BLACK_PAWN) && (c < FIG_RED_TYPE);
    } else {
        // Black turn
        return (c < FIG_BLACK_PAWN) && c;
    }
}

void Field::tryMove(Sint8 _x, Sint8 _y) {
    // Checking getting over border
    if (_y < 0 || _y >= FIELD_WIDTH) {
        return;
    }
    // Setting new state
    if (figures[getPos(_x, _y)] == FIG_NONE) {
        // Setting new position
        figures[getPos(_x, _y)] = FIG_MOVE_TO;
        wasMoven = true;
    }
}

void Field::tryAttack(Sint8 _x, Sint8 _y) {
    // Checking getting over border
    if (_x < 0 || _x >= FIELD_WIDTH || _y < 0 || _y >= FIELD_WIDTH) {
        return;
    }
    if (isAttackable(getPos(_x, _y))) {
        // Setting figure to be attacked
        figures[getPos(_x, _y)] += FIG_RED_TYPE;
        wasMoven = true;
    }
}

bool Field::tryMoveTo(position pos) {
    // Checking on getting on figure
    if (figures[pos]) {
        // Checking, if that figure attackable (in opposite command)
        if (isAttackable(pos)) {
            // Making figure attackable
            figures[pos] += FIG_RED_TYPE;
            wasMoven = true;
        }
        // Breaking cycle
        return true;
    }
    // Setting point to move to
    figures[pos] = FIG_MOVE_TO;
    wasMoven = true;

    // Normal return
    return false;
}

void Field::setDiagonals(coord _x, coord _y) {
    // Diagonal to left up
    for (int x = _x-1; (x >= 0) && (_y - _x + x >= 0); --x) {
        if (tryMoveTo(getPos(x, _y - _x + x))) {
            break;
        }
    }

    // Diagonal to down right
    for (int x = _x+1; (x < FIELD_WIDTH) && (_y - _x + x < FIELD_WIDTH); ++x) {
        if (tryMoveTo(getPos(x, _y - _x + x))) {
            break;
        }
    }

    // Diagonal to down left
    for (int x = _x - 1; (x >= 0) && (_y + _x - x < FIELD_WIDTH); --x) {
        if (tryMoveTo(getPos(x, _y + _x - x))) {
            break;
        }
    }

    // Diagonal to up right
    for (int x = _x + 1; (x < FIELD_WIDTH) && (_y + _x - x >= 0); ++x) {
        if (tryMoveTo(getPos(x, _y + _x - x))) {
            break;
        }
    }
}

void Field::setStraight(coord _x, coord _y) {
    // To left part
    for (int i = _x-1; i >= 0; --i) {
        if (tryMoveTo(getPos(i, _y))) {
            break;
        }
    }

    // To right part
    for (int i = _x+1; i < FIELD_WIDTH; ++i) {
        if (tryMoveTo(getPos(i, _y))) {
            break;
        }
    }

    // To up part
    for (int i = _y-1; i >= 0; --i) {
        if (tryMoveTo(getPos(_x, i))) {
            break;
        }
    }

    // To down part
    for (int i = _y+1; i < FIELD_WIDTH; ++i) {
        if (tryMoveTo(getPos(_x, i))) {
            break;
        }
    }
}

void Field::setAround(coord _x, coord _y, const Sint8 _moves[][2]) {
    // Checking all cells in array
    for (Uint8 i=0; i < 8; ++i) {
        Sint8 x = _x + _moves[i][0];
        Sint8 y = _y + _moves[i][1];
        // Checking on getting over border
        if ((x >= 0) && (x < FIELD_WIDTH) && (y >= 0) && (y < FIELD_WIDTH)) {
            if (figures[getPos(x, y)] == FIG_NONE) {
                // Checking on free cell
                figures[getPos(x, y)] = FIG_MOVE_TO;
                wasMoven = true;
            } else if (isAttackable(getPos(x, y))) {
                // Checking on attackable cell
                figures[getPos(x, y)] += FIG_RED_TYPE;
                wasMoven = true;
            }
        }
    }
}

void Field::setCastlingLeft(coord _x, coord _y, cell _need) {
    // Checking, if all space between is free
    for (int x = _x-1; x >= 0; --x) {
        // Check, if need cell
        if (figures[getPos(x, _y)] == _need) {
            // Set cell to can swap
            figures[getPos(x, _y)] += FIG_RED_TYPE;
            // Returning
            return;
        } else if (figures[getPos(x, _y)] != FIG_NONE) {
            // Check, if place free
            return;
        }
    }
    // Return, if don't find need cell
    return;
}

void Field::setCastlingRight(coord _x, coord _y, cell _need) {
    // Checking, if all space between is free
    for (int x = _x + 1; x < FIELD_WIDTH; ++x) {
        // Check, if need cell
        if (figures[getPos(x, _y)] == _need) {
            // Set cell to can swap
            figures[getPos(x, _y)] += FIG_RED_TYPE;
            // Returning
            return;
        } else if (figures[getPos(x, _y)] != FIG_NONE) {
            // Check, if place free
            return;
        }
    }
    // Return, if don't find need cell
    return;
}
