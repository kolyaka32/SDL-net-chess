/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "board.hpp"
#include "../internet/internet.hpp"


Board::Board()
: Field(),
rect({LEFT_LINE, UPPER_LINE, GAME_WIDTH, GAME_HEIGHT}),
activeCell(FIG_NONE),
activePosition(0, 0) {}

Board& Board::operator=(const Field& _field) {
    *this = _field;

    return *this;
}

void Board::resetSelection() {
    // Resetting selected figure
    activeCell = FIG_NONE;

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

void Board::pickFigure(Position _p) {
    // Finding clicked cell, it position
    activePosition = _p;
    activeCell = figures[_p.getPosition()];

    // Resetting flag of moving figure
    wasMoven = false;

    // Checking, which color is active
    if (state == GameState::CurrentPlay) {
        // White figures turn
        // Setting positions of cell, where active can go, depend on figure
        switch (activeCell) {
        case FIG_WHITE_PAWN:
            // Basic move
            tryMove(_p - Position(0, 1));

            // Check, if in start position and wasn't any move
            if (wasMoven && _p.y == FIELD_WIDTH - 2) {
                tryMove(_p - Position(0, 2));
            }

            // Attack positions
            tryAttack(_p - Position(-1, 1));
            tryAttack(_p - Position( 1, 1));
            break;

        case FIG_WHITE_BISHOP:
            setDiagonals(_p);
            break;

        case FIG_WHITE_ROOK:
            // Check castling
            if (castling & CASTLING_W_Q) {
                setCastlingRight(_p, FIG_WHITE_KING);
            }
            if (castling & CASTLING_W_K) {
                setCastlingLeft(_p, FIG_WHITE_KING);
            }
            // Main move
            setStraight(_p);
            break;

        case FIG_WHITE_KNIGHT:
            setAroundKnight(_p);
            break;

        case FIG_WHITE_QUEEN:
            setDiagonals(_p);
            setStraight(_p);
            break;

        case FIG_WHITE_KING:
            // Check castling
            if (castling & CASTLING_W_Q) {
                setCastlingLeft(_p, FIG_WHITE_ROOK);
            }
            if (castling & CASTLING_W_K) {
                setCastlingRight(_p, FIG_WHITE_ROOK);
            }
            // Main move
            setAroundKing(_p);
            break;
        }
    } else {
        // Black figures turn
        // Setting positions of cell, where active can go, depend on figure
        switch (activeCell) {
        case FIG_BLACK_PAWN:
            // Basic move
            tryMove(_p + Position(0, 1));

            // Check, if in start position and wasn't any move
            if (wasMoven && _p.y == 1) {
                tryMove(_p + Position(0, 2));
            }

            // Attack positions
            tryAttack(_p + Position(-1, 1));
            tryAttack(_p + Position( 1, 1));
            break;

        case FIG_BLACK_BISHOP:
            setDiagonals(_p);
            break;

        case FIG_BLACK_ROOK:
            // Check castling
            if (castling & CASTLING_B_Q) {
                setCastlingRight(_p, FIG_BLACK_KING);
            }
            if (castling & CASTLING_B_K) {
                setCastlingLeft(_p, FIG_BLACK_KING);
            }
            // Main move
            setStraight(_p);
            break;

        case FIG_BLACK_KNIGHT:
            setAroundKnight(_p);
            break;

        case FIG_BLACK_QUEEN:
            setDiagonals(_p);
            setStraight(_p);
            break;

        case FIG_BLACK_KING:
            // Check castling
            if (castling & CASTLING_B_Q) {
                setCastlingLeft(_p, FIG_BLACK_ROOK);
            }
            if (castling & CASTLING_B_K) {
                setCastlingRight(_p, FIG_BLACK_ROOK);
            }
            // Main move
            setAroundKing(_p);
            break;
        }
    }
    // Checking, if wasn't any move
    if (!wasMoven) {
        activeCell = FIG_NONE;
        return;
    }
    return;
}

void Board::placeFigure(Position _p) {
    // Check on game end
    if (state == GameState::CurrentPlay) {
        // Checking on game end (if there king of another command)
        if (figures[_p.getPosition()] == FIG_RED_TYPE + FIG_BLACK_KING) {
            state = GameState::CurrentWin;
            return;
        }
    } else {
        // Checking on game end (if there king of another command)
        if (figures[_p.getPosition()] == FIG_RED_TYPE + FIG_WHITE_KING) {
            state = GameState::OpponentWin;
            return;
        }
    }
    bool makeMove = true;  // Flag of normal turn

    // Check on special moves (castling and pawn transform)
    switch (activeCell) {
    case FIG_WHITE_ROOK:
        // Disabling posible castling for next turns
        if (activePosition == Position(0, 7)) {
            castling &= CASTLING_B_K | CASTLING_B_Q | CASTLING_W_K;
        }
        if (activePosition == Position(7, 7)) {
            castling &= CASTLING_B_K | CASTLING_B_Q | CASTLING_W_Q;
        }

        // Check, if castling
        if (figures[_p.getPosition()] == FIG_WHITE_KING + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activePosition.getPosition()] = FIG_NONE;
            figures[60] = FIG_NONE;
            // Resetting castling for next turns
            castling &= CASTLING_B_K | CASTLING_B_Q;

            // Setting rook to new place
            if (activePosition.x < FIELD_WIDTH/2) {
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
        if (figures[_p.getPosition()] == FIG_WHITE_ROOK + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activePosition.getPosition()] = FIG_NONE;
            figures[_p.x+56] = FIG_NONE;

            // Disabling previous cell clearing
            if (_p.x < FIELD_WIDTH/2) {
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
        if (activePosition == Position(0, 0)) {
            castling &= CASTLING_W_K | CASTLING_W_Q | CASTLING_B_K;
        }
        if (activePosition == Position(7, 0)) {
            castling &= CASTLING_W_K | CASTLING_W_Q | CASTLING_B_Q;
        }

        // Check, if castling
        if (figures[_p.getPosition()] == FIG_BLACK_KING + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activePosition.getPosition()] = FIG_NONE;
            figures[4] = FIG_NONE;
            // Disabling posible castling for next turns
            castling &= CASTLING_W_Q | CASTLING_W_K;

            // Disabling previous cell clearing
            if (activePosition.x < FIELD_WIDTH/2) {
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
        if (figures[_p.getPosition()] == FIG_BLACK_ROOK + FIG_RED_TYPE) {
            makeMove = false;
            // Clearing current figures
            figures[activePosition.getPosition()] = FIG_NONE;
            figures[_p.x] = FIG_NONE;

            // Disabling previous cell clearing
            if (_p.x < FIELD_WIDTH/2) {
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
        if (_p.y == (FIELD_WIDTH - 1)) {
            activeCell = FIG_BLACK_QUEEN;
        }
        break;

    case FIG_WHITE_PAWN:
        // Check, if on last line - convert into queen
        if (_p.y == 0) {
            activeCell = FIG_WHITE_QUEEN;
        }
        break;
    }
    // Setting new position to cell (if wasn't castling)
    if (makeMove) {
        figures[_p.getPosition()] = activeCell;
        figures[activePosition.getPosition()] = FIG_NONE;
    }

    // Making sound
    audio.sounds.play(Sounds::Turn);

    // Clearing field after turn
    resetSelection();

    // Changing moving player
    if (state == GameState::CurrentPlay) {
        state = GameState::OpponentPlay;
    } else {
        state = GameState::CurrentPlay;
    }
}

bool Board::isValid(const Mouse _mouse) {
    return _mouse.in(rect);
}

Position Board::getPosition(const Mouse _mouse) {
    return Position((_mouse.getX()-rect.x)/CELL_SIDE,
        (_mouse.getY()-rect.y)/CELL_SIDE);
}

void Board::clickCooperative(const Mouse mouse) {
    /*
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
        return placeFigure(pos);
    }
    // Return, that nothing happen
    return END_NONE;*/
}

void Board::clickServer(const Mouse mouse) {
    // Emulating first click on field
    /*pickFigure(_p1);

    // Emulating second click on field
    if (figures[_p2.getPosition()] >= FIG_MOVE_TO) {
        Uint8 turn = placeFigure(_p2);
        // Resetting field for correct next turns
        resetSelection();
        return turn;
    }
    return END_NONE;*/
}

void Board::clickClient(const Mouse mouse) {
    //internet.sendAllConfirmed({ConnectionCode::GameTurn, getLastTurn(mouse)});
}

void Board::blit(const Window& _window) const {
    // Drawing global background
    _window.setDrawColor(BLACK);
    _window.clear();

    // Drawing field light part
    _window.setDrawColor(FIELD_LIGHT);
    _window.drawRect(rect);

    // One cell fro rendering
    SDL_FRect cellRect = {0, 0, CELL_SIDE, CELL_SIDE};

    // Fill drawing dark part of background
    _window.setDrawColor(FIELD_DARK);

    // Drawing each figure
    for (coord y = 0; y < FIELD_WIDTH; ++y)
        for (coord x = 0; x < FIELD_WIDTH; ++x) {
            // Getting rect
            cellRect.x = rect.x + x*CELL_SIDE;
            cellRect.y = rect.y + y*CELL_SIDE;

            // Draw dark part
            if ((x + y) % 2) {
                _window.drawRect(cellRect);
            }

            // Getting type of
            cell type = figures[y * FIELD_WIDTH + x];

            // Drawing figures
            if (type) {
                // Checking, if figure current (blue)
                if (type > FIG_RED_TYPE) {
                    // Getting textyre
                    SDL_Texture* textureIndex = _window.getTexture(Textures::WhitePawn - 1 + type - FIG_RED_TYPE);

                    // Checking, if figure attackable (red)
                    // Making it red
                    _window.setColorMode(textureIndex, RED);

                    // Drawing
                    _window.blit(textureIndex, cellRect);

                    // Resetting cell color
                    _window.setColorMode(textureIndex);
                } else {
                    _window.blit(_window.getTexture(Textures::WhitePawn - 1 + type), cellRect);
                }
            }
        }

    // Draw selected figure
    if (activeCell) {
        SDL_Texture* textureIndex = _window.getTexture(Textures::WhitePawn - 1 + activeCell);
        // Making it blue
        _window.setColorMode(textureIndex, BLUE);

        // Draw it
        cellRect.x = rect.x + activePosition.x*CELL_SIDE;
        cellRect.y = rect.y + activePosition.y*CELL_SIDE;
        _window.blit(textureIndex, cellRect);

        // Resetting color
        _window.setColorMode(textureIndex);
    }
}
