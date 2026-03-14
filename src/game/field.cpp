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
    // Copying cell by cell with removing selection
    for (int i=0; i < sqr(FIELD_WIDTH); ++i) {
        figures[i] = _field.figures[i] & CELL_TYPE_MASK;
    }
}

Field& Field::operator=(const Field& _field) {
    memcpy(figures, _field.figures, sizeof(figures));
    state = _field.state;
    castling = _field.castling;
    wasMoven = false;
    return *this;
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

bool Field::isAttackable(Position _pos) const {
    cell c = figures[_pos.getPosition()];
    if (state == GameState::CurrentPlay) {
        // White turn
        return (c >= FIG_BLACK_PAWN) && (c < FIG_RED_TYPE);
    } else {
        // Black turn
        return (c < FIG_BLACK_PAWN) && c;
    }
}

void Field::tryMove(Position _pos) {
    // Checking getting over border
    if (_pos.y < 0 || _pos.y >= FIELD_WIDTH) {
        return;
    }
    // Setting new state
    if (figures[_pos.getPosition()] == FIG_NONE) {
        // Setting new position
        figures[_pos.getPosition()] = FIG_MOVE_TO;
        wasMoven = true;
    }
}

void Field::tryAttack(Position _pos) {
    // Checking getting over border
    if (_pos.x < 0 || _pos.x >= FIELD_WIDTH || _pos.y < 0 || _pos.y >= FIELD_WIDTH) {
        return;
    }
    if (isAttackable(_pos)) {
        // Setting figure to be attacked
        figures[_pos.getPosition()] += FIG_RED_TYPE;
        wasMoven = true;
    }
}

bool Field::tryMoveTo(Position _pos) {
    // Checking on getting on figure
    if (figures[_pos.getPosition()]) {
        // Checking, if that figure attackable (in opposite command)
        if (isAttackable(_pos)) {
            // Making figure attackable
            figures[_pos.getPosition()] += FIG_RED_TYPE;
            wasMoven = true;
        }
        // Breaking cycle
        return true;
    }
    // Setting point to move to
    figures[_pos.getPosition()] = FIG_MOVE_TO;
    wasMoven = true;

    // Normal return
    return false;
}

void Field::setDiagonals(Position _pos) {
    // Diagonal to left up
    for (int x = _pos.x-1; (x >= 0) && (_pos.y - _pos.x + x >= 0); --x) {
        if (tryMoveTo(Position(x, _pos.y - _pos.x + x))) {
            break;
        }
    }

    // Diagonal to down right
    for (int x = _pos.x+1; (x < FIELD_WIDTH) && (_pos.y - _pos.x + x < FIELD_WIDTH); ++x) {
        if (tryMoveTo(Position(x, _pos.y - _pos.x + x))) {
            break;
        }
    }

    // Diagonal to down left
    for (int x = _pos.x - 1; (x >= 0) && (_pos.y + _pos.x - x < FIELD_WIDTH); --x) {
        if (tryMoveTo(Position(x, _pos.y + _pos.x - x))) {
            break;
        }
    }

    // Diagonal to up right
    for (int x = _pos.x + 1; (x < FIELD_WIDTH) && (_pos.y + _pos.x - x >= 0); ++x) {
        if (tryMoveTo(Position(x, _pos.y + _pos.x - x))) {
            break;
        }
    }
}

void Field::setStraight(Position _pos) {
    // To left part
    for (int i = _pos.x-1; i >= 0; --i) {
        if (tryMoveTo(Position(i, _pos.y))) {
            break;
        }
    }

    // To right part
    for (int i = _pos.x+1; i < FIELD_WIDTH; ++i) {
        if (tryMoveTo(Position(i, _pos.y))) {
            break;
        }
    }

    // To up part
    for (int i = _pos.y-1; i >= 0; --i) {
        if (tryMoveTo(Position(_pos.x, i))) {
            break;
        }
    }

    // To down part
    for (int i = _pos.y+1; i < FIELD_WIDTH; ++i) {
        if (tryMoveTo(Position(_pos.x, i))) {
            break;
        }
    }
}

void Field::setAroundKing(Position _pos) {
    // Checking all cells in array
    for (Uint8 i=0; i < 8; ++i) {
        Position pos = _pos + kingMoves[i];
        // Checking on getting over border
        if ((pos.x >= 0) && (pos.x < FIELD_WIDTH) && (pos.y >= 0) && (pos.y < FIELD_WIDTH)) {
            if (figures[pos.getPosition()] == FIG_NONE) {
                // Checking on free cell
                figures[pos.getPosition()] = FIG_MOVE_TO;
                wasMoven = true;
            } else if (isAttackable(pos)) {
                // Checking on attackable cell
                figures[pos.getPosition()] += FIG_RED_TYPE;
                wasMoven = true;
            }
        }
    }
}

void Field::setAroundKnight(Position _pos) {
    // Checking all cells in array
    for (Uint8 i=0; i < 8; ++i) {
        Position pos = _pos + knightMoves[i];
        // Checking on getting over border
        if ((pos.x >= 0) && (pos.x < FIELD_WIDTH) && (pos.y >= 0) && (pos.y < FIELD_WIDTH)) {
            if (figures[pos.getPosition()] == FIG_NONE) {
                // Checking on free cell
                figures[pos.getPosition()] = FIG_MOVE_TO;
                wasMoven = true;
            } else if (isAttackable(pos)) {
                // Checking on attackable cell
                figures[pos.getPosition()] += FIG_RED_TYPE;
                wasMoven = true;
            }
        }
    }
}

void Field::setCastlingLeft(Position _pos, cell _need) {
    // Checking, if all space between is free
    for (int x = _pos.x-1; x >= 0; --x) {
        // Get need cell
        position pos = Position(x, _pos.y).getPosition();
        // Check, if need cell
        if (figures[pos] == _need) {
            // Set cell to can swap
            figures[pos] += FIG_RED_TYPE;
            // Returning
            return;
        } else if (figures[pos] != FIG_NONE) {
            // Check, if place don't free
            return;
        }
    }
}

void Field::setCastlingRight(Position _pos, cell _need) {
    // Checking, if all space between is free
    for (int x = _pos.x + 1; x < FIELD_WIDTH; ++x) {
        // Get need cell
        position pos = Position(x, _pos.y).getPosition();
        // Check, if need cell
        if (figures[pos] == _need) {
            // Set cell to can swap
            figures[pos] += FIG_RED_TYPE;
            // Returning
            return;
        } else if (figures[pos] != FIG_NONE) {
            // Check, if place don't free
            return;
        }
    }
}
