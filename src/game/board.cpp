/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"

// Configuration of board, for play
char boardConfig[85] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";


Position::Position(const Mouse _mouse)
: x((_mouse.getX() - LEFT_LINE) / CELL_SIDE),
y((_mouse.getY() - UPPER_LINE) / CELL_SIDE) {}

Position::Position(const position pos)
: x(pos%FIELD_WIDTH), y(pos/FIELD_WIDTH) {}

Position::Position(coord _x, coord _y)
: x(_x), y(_y) {}

position Position::getPosition() {
    return x + y*FIELD_WIDTH;
}


// Clearing field and setting
void Board::reset() {
    // Resetting field parametrs
    resetField();
    activeCell.type = FIG_NONE;  // None cell selected
    castling = 0;                // All castlings not possible

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
    for (; boardConfig[i] && (c < sqr(FIELD_WIDTH)); ++i) {
        switch (boardConfig[i]) {
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
            c += boardConfig[i] - '0';
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
    for (; boardConfig[i]; ++i) {
        switch (boardConfig[i]) {
        // Starting player config
        case 'w':
        case 'W':
            turn = TURN_WHITE;
            break;

        case 'b':
        case 'B':
            turn = TURN_BLACK;
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

// Drawing all figures with background
void Board::blit(const Window& _target) const {
    // Drawing global background
    _target.setDrawColor(BLACK);
    _target.clear();

    // Drawing field light part
    _target.setDrawColor(FIELD_LIGHT);
    _target.drawRect({LEFT_LINE, UPPER_LINE, GAME_WIDTH, GAME_HEIGHT});

    // Drawing background
    _target.setDrawColor(FIELD_DARK);
    for (coord y = 0; y < FIELD_WIDTH; ++y)
        for (coord x = y % 2; x < FIELD_WIDTH; x += 2) {
            _target.drawRect(getRect({x, y}));
        }

    // Drawing each figure
    for (coord y = 0; y < FIELD_WIDTH; ++y)
        for (coord x = 0; x < FIELD_WIDTH; ++x) {
            if (figures[getPos(x, y)]) {
                SDL_FRect rect = getRect({x, y});

                // Checking, if figure current (blue)
                if (figures[getPos(x, y)] > FIG_RED_TYPE) {
                    // Getting textyre
                    IMG_names textureIndex = IMG_names(IMG_GAME_WHITE_PAWN - 1 + figures[getPos(x, y)] - FIG_RED_TYPE);

                    // Checking, if figure attackable (red)
                    // Making it red
                    _target.setColorMode(textureIndex, RED);

                    // Drawing
                    _target.blit(textureIndex, rect);

                    // Resetting cell color
                    _target.setColorMode(textureIndex);
                } else {
                    _target.blit(IMG_names(IMG_GAME_WHITE_PAWN - 1 + figures[getPos(x, y)]), rect);
                }
            }
        }

    // Draw selected figure
    if (activeCell.type) {
        IMG_names textureIndex = IMG_names(IMG_GAME_WHITE_PAWN - 1 + activeCell.type);
        // Making it blue
        _target.setColorMode(textureIndex, BLUE);

        // Draw
        _target.blit(textureIndex, getRect(activeCell.pos));

        // Resetting color
        _target.setColorMode(textureIndex);
    }
}

// Clear all selected figures
void Board::resetSelection() {
    // Resetting selected figure
    activeCell.type = FIG_NONE;

    // Clearing field after turn (resetting figure move to and red type)
    for (position i=0; i < sqr(FIELD_WIDTH); ++i) {
        // Clear points to move
        if (figures[i] == FIG_MOVE_TO) {
            figures[i] = FIG_NONE;
        } else {
            // Clearing all extra codes
            figures[i] &= (FIG_RED_TYPE-1);
        }
    }
}

// Function of picking figure from field
void Board::pickFigure(Position p) {
    // Finding clicked cell, it position
    activeCell.pos = p.getPosition();
    activeCell.type = figures[activeCell.pos];

    // Resetting flag of moving figure
    wasMoven = false;

    // Checking, which color is active
    if (turn == TURN_WHITE) {
        // White figures turn
        // Setting positions of cell, where active can go, depend on figure
        switch (activeCell.type) {
        case FIG_WHITE_PAWN:
            // Basic move
            tryMove(p.x, p.y - 1);

            // Check, if in start position and wasn't any move
            if (wasMoven && p.y == FIELD_WIDTH - 2) {
                tryMove(p.x, p.y - 2);
            }

            // Attack positions
            tryAttack(p.x-1, p.y-1);
            tryAttack(p.x+1, p.y-1);
            break;

        case FIG_WHITE_BISHOP:
            setDiagonals(p.x, p.y);
            break;

        case FIG_WHITE_ROOK:
            // Check castling
            if (castling & CASTLING_W_Q) {
                setCastlingRight(p.x, p.y, FIG_WHITE_KING);
            }
            if (castling & CASTLING_W_K) {
                setCastlingLeft(p.x, p.y, FIG_WHITE_KING);
            }
            // Main move
            setStraight(p.x, p.y);
            break;

        case FIG_WHITE_KNIGHT:
            setAround(p.x, p.y, knightMoves);
            break;

        case FIG_WHITE_QUEEN:
            setDiagonals(p.x, p.y);
            setStraight(p.x, p.y);
            break;

        case FIG_WHITE_KING:
            // Check castling
            if (castling & CASTLING_W_Q) {
                setCastlingLeft(p.x, p.y, FIG_WHITE_ROOK);
            }
            if (castling & CASTLING_W_K) {
                setCastlingRight(p.x, p.y, FIG_WHITE_ROOK);
            }
            // Main move
            setAround(p.x, p.y, kingMoves);
            break;
        }
    } else {
        // Black figures turn
        // Setting positions of cell, where active can go, depend on figure
        switch (activeCell.type) {
        case FIG_BLACK_PAWN:
            // Basic move
            tryMove(p.x, p.y + 1);

            // Check, if in start position and wasn't any move
            if (wasMoven && p.y == 1) {
                tryMove(p.x, p.y + 2);
            }

            // Attack positions
            tryAttack(p.x-1, p.y+1);
            tryAttack(p.x+1, p.y+1);
            break;

        case FIG_BLACK_BISHOP:
            setDiagonals(p.x, p.y);
            break;

        case FIG_BLACK_ROOK:
            // Check castling
            if (castling & CASTLING_B_Q) {
                setCastlingRight(p.x, p.y, FIG_BLACK_KING);
            }
            if (castling & CASTLING_B_K) {
                setCastlingLeft(p.x, p.y, FIG_BLACK_KING);
            }
            // Main move
            setStraight(p.x, p.y);
            break;

        case FIG_BLACK_KNIGHT:
            setAround(p.x, p.y, knightMoves);
            break;

        case FIG_BLACK_QUEEN:
            setDiagonals(p.x, p.y);
            setStraight(p.x, p.y);
            break;

        case FIG_BLACK_KING:
            // Check castling
            if (castling & CASTLING_B_Q) {
                setCastlingLeft(p.x, p.y, FIG_BLACK_ROOK);
            }
            if (castling & CASTLING_B_K) {
                setCastlingRight(p.x, p.y, FIG_BLACK_ROOK);
            }
            // Main move
            setAround(p.x, p.y, kingMoves);
            break;
        }
    }
    // Checking, if wasn't any move
    if (!wasMoven) {
        activeCell.type = FIG_NONE;
        return;
    }
    return;
}

Uint8 Board::placeFigure(const Sounds& _sounds, Position p) {
    // Check on game end
    if (turn == TURN_WHITE) {
        // Checking on game end (if there king of another command)
        if (figures[p.getPosition()] == FIG_RED_TYPE + FIG_BLACK_KING) {
            return END_WIN + turn;
        }
    } else {
        // Checking on game end (if there king of another command)
        if (figures[p.getPosition()] == FIG_RED_TYPE + FIG_WHITE_KING) {
            return END_WIN + turn;
        }
    }
    bool makeMove = true;  // Flag of normal turn

    // Check on special moves (castling and pawn transform)
    switch (activeCell.type) {
    case FIG_WHITE_ROOK:
        // Disabling posible castling for next turns
        if (activeCell.pos == getPos(0, 7)) {
            castling &= CASTLING_B_K | CASTLING_B_Q | CASTLING_W_K;
        }
        if (activeCell.pos == getPos(7, 7)) {
            castling &= CASTLING_B_K | CASTLING_B_Q | CASTLING_W_Q;
        }

        // Check, if castling
        if (figures[p.getPosition()] == FIG_WHITE_KING + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[60] = FIG_NONE;
            // Resetting castling for next turns
            castling &= CASTLING_B_K | CASTLING_B_Q;

            // Setting rook to new place
            if (activeCell.pos % FIELD_WIDTH < FIELD_WIDTH/2) {
                figures[59] = FIG_WHITE_ROOK;
                figures[58] = FIG_WHITE_KING;
            } else {
                figures[61] = FIG_WHITE_ROOK;
                figures[62] = FIG_WHITE_KING;
            }
        }
        break;

    case FIG_WHITE_KING:
        // Disabling posible castling for next turns
        castling &= CASTLING_B_Q | CASTLING_B_K;

        // Check, if castling
        if (figures[p.getPosition()] == FIG_WHITE_ROOK + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[p.x+56] = FIG_NONE;

            // Disabling previous cell clearing
            if (p.x < FIELD_WIDTH/2) {
                figures[58] = FIG_WHITE_KING;
                figures[59] = FIG_WHITE_ROOK;
            } else {
                figures[62] = FIG_WHITE_KING;
                figures[61] = FIG_WHITE_ROOK;
            }
        }
        break;

    case FIG_BLACK_ROOK:
        // Disabling posible castling for next turns
        if (activeCell.pos == getPos(0, 0)) {
            castling &= CASTLING_W_K | CASTLING_W_Q | CASTLING_B_K;
        }
        if (activeCell.pos == getPos(7, 0)) {
            castling &= CASTLING_W_K | CASTLING_W_Q | CASTLING_B_Q;
        }

        // Check, if castling
        if (figures[p.getPosition()] == FIG_BLACK_KING + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[4] = FIG_NONE;
            // Disabling posible castling for next turns
            castling &= CASTLING_W_Q | CASTLING_W_K;

            // Disabling previous cell clearing
            if (activeCell.pos % FIELD_WIDTH < FIELD_WIDTH/2) {
                figures[3] = FIG_BLACK_ROOK;
                figures[2] = FIG_BLACK_KING;
            } else {
                figures[5] = FIG_BLACK_ROOK;
                figures[6] = FIG_BLACK_KING;
            }
        }
        break;

    case FIG_BLACK_KING:
        // Disabling posible castling for next turns
        castling &= CASTLING_W_Q | CASTLING_W_K;

        // Check, if castling
        if (figures[p.getPosition()] == FIG_BLACK_ROOK + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[p.x] = FIG_NONE;

            // Disabling previous cell clearing
            if (p.x < FIELD_WIDTH/2) {
                figures[2] = FIG_BLACK_KING;
                figures[3] = FIG_BLACK_ROOK;
            } else {
                figures[6] = FIG_BLACK_KING;
                figures[5] = FIG_BLACK_ROOK;
            }
        }
        break;

    case FIG_BLACK_PAWN:
        // Check, if on last line - convert into queen
        if (p.y == FIELD_WIDTH - 1) {
            activeCell.type = FIG_BLACK_QUEEN;
        }
        break;

    case FIG_WHITE_PAWN:
        // Check, if on last line - convert into queen
        if (p.y == 0) {
            activeCell.type = FIG_WHITE_QUEEN;
        }
        break;
    }
    // Setting new position to cell (if wasn't castling)
    if (makeMove) {
        figures[p.getPosition()] = activeCell.type;
        figures[activeCell.pos] = FIG_NONE;
    }

    // Making sound
    _sounds.play(SND_TURN);

    // Clearing field after turn
    resetSelection();

    // Changing moving player
    turn = !turn;

    // Shwoing making turn
    return END_TURN;
}

Uint8 Board::click(const Sounds& _sounds, const Mouse _mouse) {
    // Check, if get over field borders
    if (_mouse.getX() > LEFT_LINE && _mouse.getX() < LEFT_LINE+GAME_WIDTH
        && _mouse.getY() > UPPER_LINE && _mouse.getY() < UPPER_LINE+GAME_WIDTH) {
        return click(_sounds, Position{_mouse});
    }
    return END_NONE;
}

// Clicking on field (grab and put figures)
Uint8 Board::click(const Sounds& _sounds, Position pos) {
    // Checking, which type of action do
    if (!activeCell.type) {
        // Picking up figure from field
        pickFigure(pos);

        // Return, that don't do anything
        return END_NONE;
    } else if (activeCell.pos == pos.getPosition()) {
        // Checking, if click on old place
        // Clearing field for next turns
        resetSelection();

        // Returning, that nothing happen
        return END_NONE;
    // Checking, if click on avalible position
    } else if (figures[pos.getPosition()] >= FIG_MOVE_TO) {
        // Set last position as current
        endPosition = pos.getPosition();
        // Placing figure there
        return placeFigure(_sounds, pos);
    }
    // Return, that nothing happen
    return END_NONE;
}

// Making all like in click, but at once and without help
Uint8 Board::move(const Sounds& _sounds, Position _p1, Position _p2) {
    // Emulating first click on field
    pickFigure(_p1);

    // Emulating second click on field
    if (figures[_p2.getPosition()] >= FIG_MOVE_TO) {
        Uint8 turn = placeFigure(_sounds, _p2);
        // Resetting field for correct next turns
        resetSelection();
        return turn;
    }
    return END_NONE;
}

SDL_FRect Board::getRect(Position pos) const {
    return {
        float(LEFT_LINE + pos.x * CELL_SIDE),
        float(UPPER_LINE + pos.y * CELL_SIDE),
        CELL_SIDE,
        CELL_SIDE
    };
}

Uint8 Board::currentTurn() const {
    return turn;
}

bool Board::isFigureSelected() const {
    return activeCell.type;
}

position Board::getLastTurnStart() const {
    return activeCell.pos;
}
position Board::getLastTurnEnd() const {
    return endPosition;
}
