/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include <cstdlib>
#include <cstring>
#include "figuresMoves.hpp"


FiguresMoves::FiguresMoves() {
    // Firstly resetting all figures
    resetField();
}

FiguresMoves::FiguresMoves(const FiguresMoves& _field)
: state(_field.state),
castling(_field.castling),
wasMoven(_field.wasMoven),
saveTime(_field.saveTime) {
    memcpy(figures, _field.figures, sizeof(figures));
}

FiguresMoves::FiguresMoves(const char* _saveText) {
    resetField();
    // Loading from field from text
    // !
    // Forsyth–Edwards Notation
    // White figures: pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K"
    // Black figures - "pnbrqk"
    // 1-8 - spaces between figures
    // '\', '/' - lines separator
    // 'w', 'l' - which command start

    // Base notation:
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    // Setting figures on them places by given text
    position c = 0;  // Counter of place on field

    // Parsing text for setting figures
    unsigned i=0;
    for (; _saveText[i] && (c < sqr(FIELD_WIDTH)); ++i) {
        switch (_saveText[i]) {
        // White figures
        case 'K':
            figures[c++] = FIG_WHITE_KING;
            break;

        case 'Q':
            figures[c++] = FIG_WHITE_QUEEN;
            break;

        case 'R':
            figures[c++] = FIG_WHITE_ROOK;
            break;

        case 'B':
            figures[c++] = FIG_WHITE_BISHOP;
            break;

        case 'N':
            figures[c++] = FIG_WHITE_KNIGHT;
            break;

        case 'P':
            figures[c++] = FIG_WHITE_PAWN;
            break;

        // Black figures
        case 'k':
            figures[c++] = FIG_BLACK_KING;
            break;

        case 'q':
            figures[c++] = FIG_BLACK_QUEEN;
            break;

        case 'r':
            figures[c++] = FIG_BLACK_ROOK;
            break;

        case 'b':
            figures[c++] = FIG_BLACK_BISHOP;
            break;

        case 'n':
            figures[c++] = FIG_BLACK_KNIGHT;
            break;

        case 'p':
            figures[c++] = FIG_BLACK_PAWN;
            break;

        // Spaces between
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            c += _saveText[i] - '0';
            break;

        // Line separator
        case '\\':
        case '/':
            // Checking, if not on another line
            if (c % FIELD_WIDTH) {
                // Forced going to next line
                c = ((c-1) / FIELD_WIDTH + 1) * FIELD_WIDTH;
            }
            break;

        // Separator of second part
        case ' ':
            c = 64;
            break;
        }
    }
    // Parsing last part of text for rest data
    for (; _saveText[i]; ++i) {
        switch (_saveText[i]) {
        // Starting player config
        case 'w':
        case 'W':
            state = GameState::CurrentPlay;
            break;

        case 'b':
        case 'B':
            state = GameState::OpponentPlay;
            break;

        // Castling posoblity
        case 'K':
            castling |= CASTLING_W_K;
            break;

        case 'Q':
            castling |= CASTLING_W_Q;
            break;

        case 'k':
            castling |= CASTLING_B_K;
            break;

        case 'q':
            castling |= CASTLING_B_Q;
            break;
        }
    }
}

const char* FiguresMoves::getSave() {
    // !
}

void FiguresMoves::resetField() {
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

bool FiguresMoves::isAttackable(position _pos) {
    cell c = figures[_pos];
    if (state == GameState::CurrentPlay) {
        // White turn
        return (c >= FIG_BLACK_PAWN) && (c < FIG_RED_TYPE);
    } else {
        // Black turn
        return (c < FIG_BLACK_PAWN) && c;
    }
}

void FiguresMoves::tryMove(Sint8 _x, Sint8 _y) {
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

void FiguresMoves::tryAttack(Sint8 _x, Sint8 _y) {
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

bool FiguresMoves::tryMoveTo(position pos) {
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

void FiguresMoves::setDiagonals(coord _x, coord _y) {
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

void FiguresMoves::setStraight(coord _x, coord _y) {
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

void FiguresMoves::setAround(coord _x, coord _y, const Sint8 _moves[][2]) {
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

void FiguresMoves::setCastlingLeft(coord _x, coord _y, cell _need) {
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

void FiguresMoves::setCastlingRight(coord _x, coord _y, cell _need) {
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
