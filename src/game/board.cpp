/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"

// Configuration of board, for play
char startBoardConfig[85] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq";

// First board clearing
Board::Board() {
    reset();
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
    Uint16 i = 0;
    for (; startBoardConfig[i] && (c < sqr(FIELD_WIDTH)); ++i) {
        switch (startBoardConfig[i]) {
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
            c += startBoardConfig[i] - '0';
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
    for (; startBoardConfig[i]; ++i) {
        switch (startBoardConfig[i]) {
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
            _target.drawRect({float(LEFT_LINE + x * CELL_SIDE), float(UPPER_LINE + y * CELL_SIDE), CELL_SIDE, CELL_SIDE});
        }

    // Drawing each figure
    for (coord y = 0; y < FIELD_WIDTH; ++y)
        for (coord x = 0; x < FIELD_WIDTH; ++x) {
            if (figures[getPos(x, y)]) {
                SDL_FRect rect = {float(LEFT_LINE + x * CELL_SIDE), float(UPPER_LINE + y * CELL_SIDE), CELL_SIDE, CELL_SIDE};
                Uint8 textureIndex = IMG_GAME_WHITE_PAWN - 1 + figures[getPos(x, y)];

                // Checking, if figure current (blue)
                if (figures[getPos(x, y)] > FIG_BLUE_TYPE) {
                    // Changing cell index to normal
                    textureIndex -= FIG_BLUE_TYPE;

                    // Making it blue
                    SDL_SetTextureColorMod(_target.getTexture(IMG_names(textureIndex)), 0, 0, 255);

                    // Drawing
                    _target.blit(IMG_names(textureIndex), rect);

                    // Resetting cell color
                    SDL_SetTextureColorMod(_target.getTexture(IMG_names(textureIndex)), 0, 0, 0);
                } else if (figures[getPos(x, y)] > FIG_RED_TYPE) {
                    // Checking, if figure attackable (red)
                    // Changing cell index to normal
                    textureIndex -= FIG_RED_TYPE;

                    // Making it red
                    SDL_SetTextureColorMod(_target.getTexture(IMG_names(textureIndex)), 255, 0, 0);

                    // Drawing
                    _target.blit(IMG_names(textureIndex), rect);

                    // Resetting cell color
                    SDL_SetTextureColorMod(_target.getTexture(IMG_names(textureIndex)), 0, 0, 0);
                } else {
                    _target.blit(IMG_names(textureIndex), rect);
                }
            }
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
void Board::pickFigure(const coord _x, const coord _y) {
    // Finding clicked cell, it position
    activeCell.pos = getPos(_x, _y);
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
            tryMove(_x, _y - 1);

            // Check, if in start position and wasn't any move
            if (wasMoven && _y == FIELD_WIDTH - 2) {
                tryMove(_x, _y - 2);
            }

            // Attack positions
            tryAttack(_x-1, _y-1);
            tryAttack(_x+1, _y-1);
            break;

        case FIG_WHITE_BISHOP:
            setDiagonals(_x, _y);
            break;

        case FIG_WHITE_ROOK:
            // Check castling
            if (castling & CASTLING_W_Q) {
                setCastlingRight(_x, _y, FIG_WHITE_KING);
            }
            if (castling & CASTLING_W_K) {
                setCastlingLeft(_x, _y, FIG_WHITE_KING);
            }
            // Main move
            setStraight(_x, _y);
            break;

        case FIG_WHITE_KNIGHT:
            setAround(_x, _y, knightMoves);
            break;

        case FIG_WHITE_QUEEN:
            setDiagonals(_x, _y);
            setStraight(_x, _y);
            break;

        case FIG_WHITE_KING:
            // Check castling
            if (castling & CASTLING_W_Q) {
                setCastlingLeft(_x, _y, FIG_WHITE_ROOK);
            }
            if (castling & CASTLING_W_K) {
                setCastlingRight(_x, _y, FIG_WHITE_ROOK);
            }
            // Main move
            setAround(_x, _y, kingMoves);
            break;
        }
    } else {
        // Black figures turn
        // Setting positions of cell, where active can go, depend on figure
        switch (activeCell.type) {
        case FIG_BLACK_PAWN:
            // Basic move
            tryMove(_x, _y + 1);

            // Check, if in start position and wasn't any move
            if (wasMoven && _y == 1) {
                tryMove(_x, _y + 2);
            }

            // Attack positions
            tryAttack(_x-1, _y+1);
            tryAttack(_x+1, _y+1);
            break;

        case FIG_BLACK_BISHOP:
            setDiagonals(_x, _y);
            break;

        case FIG_BLACK_ROOK:
            // Check castling
            if (castling & CASTLING_B_Q) {
                setCastlingRight(_x, _y, FIG_BLACK_KING);
            }
            if (castling & CASTLING_B_K) {
                setCastlingLeft(_x, _y, FIG_BLACK_KING);
            }
            // Main move
            setStraight(_x, _y);
            break;

        case FIG_BLACK_KNIGHT:
            setAround(_x, _y, knightMoves);
            break;

        case FIG_BLACK_QUEEN:
            setDiagonals(_x, _y);
            setStraight(_x, _y);
            break;

        case FIG_BLACK_KING:
            // Check castling
            if (castling & CASTLING_B_Q) {
                setCastlingLeft(_x, _y, FIG_BLACK_ROOK);
            }
            if (castling & CASTLING_B_K) {
                setCastlingRight(_x, _y, FIG_BLACK_ROOK);
            }
            // Main move
            setAround(_x, _y, kingMoves);
            break;
        }
    }
    // Checking, if wasn't any move
    if (!wasMoven) {
        activeCell.type = FIG_NONE;
        return;
    }
    // Changing color of current cell
    figures[getPos(_x, _y)] += FIG_BLUE_TYPE;
    return;
}

//
Uint8 Board::placeFigure(const Sounds& _sounds, coord _x, coord _y) {
    // Check on game end
    if (turn == TURN_WHITE) {
        // Checking on game end (if there king of another command)
        if (figures[getPos(_x, _y)] == FIG_RED_TYPE + FIG_BLACK_KING) {
            return END_WIN + turn;
        }
    } else {
        // Checking on game end (if there king of another command)
        if (figures[getPos(_x, _y)] == FIG_RED_TYPE + FIG_WHITE_KING) {
            return END_WIN + turn;
        }
    }
    bool makeMove = true;  // Flag of normal turn

    // Check on special moves (castling and pawn transform)
    switch (activeCell.type) {
    case FIG_WHITE_ROOK:
        // Disabling posible castling for next turns
        if (_x < FIELD_WIDTH/2) {
            castling |= CASTLING_B_K | CASTLING_B_Q | CASTLING_W_K;
        } else {
            castling |= CASTLING_B_K | CASTLING_B_Q | CASTLING_W_Q;
        }

        // Check, if castling
        if (figures[getPos(_x, _y)] == FIG_WHITE_KING + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[60] = FIG_NONE;

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
        if (figures[getPos(_x, _y)] == FIG_WHITE_ROOK + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[_x+56] = FIG_NONE;

            // Disabling previous cell clearing
            if (_x < FIELD_WIDTH/2) {
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
        if (_x < FIELD_WIDTH/2) {
            castling |= CASTLING_W_K | CASTLING_W_Q | CASTLING_B_K;
        } else {
            castling |= CASTLING_W_K | CASTLING_W_Q | CASTLING_B_Q;
        }

        // Check, if castling
        if (figures[getPos(_x, _y)] == FIG_BLACK_KING + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[4] = FIG_NONE;

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
        if (figures[getPos(_x, _y)] == FIG_BLACK_ROOK + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activeCell.pos] = FIG_NONE;
            figures[_x] = FIG_NONE;

            // Disabling previous cell clearing
            if (_x < FIELD_WIDTH/2) {
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
        if (_y == FIELD_WIDTH - 1) {
            activeCell.type = FIG_BLACK_QUEEN;
        }
        break;

    case FIG_WHITE_PAWN:
        // Check, if on last line - convert into queen
        if (_y == 0) {
            activeCell.type = FIG_WHITE_QUEEN;
        }
        break;
    }
    // Setting new position to cell (if wasn't castling)
    if (makeMove) {
        figures[getPos(_x, _y)] = activeCell.type;
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


// Clicking on field (grab and put figures)
Uint8 Board::click(const Sounds& _sounds, coord _x, coord _y) {
    // Checking, which type of action do
    if (!activeCell.type) {
        // Picking up figure from field
        pickFigure(_x, _y);

        // Return, that don't do anything
        return END_NONE;
    } else if (activeCell.pos == getPos(_x, _y)) {
        // Checking, if click on old place
        // Clearing field for next turns
        resetSelection();

        // Returning, that nothing happen
        return END_NONE;
    } else if (figures[getPos(_x, _y)] >= FIG_MOVE_TO) {
        // Checking, if click on avalible position
        // Placing figure there
        return placeFigure(_sounds, _x, _y);
    }
    // Return, that nothing happen
    return END_NONE;
}


// Making all like in click, but at once and without help
Uint8 Board::move(const Sounds& _sounds, coord _x1, coord _y1, coord _x2, coord _y2) {
    // Emulating first click on field
    pickFigure(_x1, _y1);

    // Emulating second click on field
    Uint8 state = click(_sounds, _x2, _y2);

    // Check, if there was turn
    if (state) {
        return state;
    } else {
        // Clearing everything after none-stated turn
        resetSelection();
        return END_NONE;
    }
}

// Return previous position, where figure was
position Board::getPreviousTurn() const {
    return activeCell.pos;
}

// Return, which of users currently moving (1/2)
Uint8 Board::currentTurn() const {
    return turn;
}

// Return, if selected any figure
bool Board::isFigureSelected() const {
    return activeCell.type;
}
