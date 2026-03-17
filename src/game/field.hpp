/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "figures.hpp"


// Types of game state
enum class GameState : Uint8 {
    CurrentPlay,
    OpponentPlay,
    CurrentWin,
    OpponentWin,
    NobodyWin,
    WaitState,
};


// Types of castling
enum CASTLING_names {
    // If castling possible from
    CASTLING_W_K = 1,  // white from king side
    CASTLING_W_Q = 2,  // white from queen side
    CASTLING_B_K = 4,  // black from king side
    CASTLING_B_Q = 8,  // black from queen side
};


// Interface of figures moves
class Field {
 protected:
    // Data for moves
    // Array of figures on field
    cell figures[sqr(FIELD_WIDTH)];
    // Flag of current game state
    GameState state;
    // Data of all now posible varhishes (ORed-together)
    Uint8 castling;
    // Flag of board, that it was moven
    bool wasMoven;

 protected:
    // Functions for interact with board
    // Reset field parametrs
    void resetField();
    // Check, if cell at need position can be attacked
    bool isAttackable(Position pos) const;
    // Try set point, where you can move
    bool tryMoveTo(Position pos);
    // Set points, where you can move or attack
    void tryMove(Position pos);
    // Try set point, where you can move
    void tryAttack(Position pos);
    // Set all cells at diagonals for movable target
    void setDiagonals(Position pos);
    // Set all cells at straight lines for movable target
    void setStraight(Position pos);
    // Set all cells around for king
    void setAroundKing(Position pos);
    // Set all cells around for knight
    void setAroundKnight(Position pos);
    // Set cells for allowing castling left to cell
    void setCastlingLeft(Position pos, cell swapableType);
    // Set cells for allowing castling right to cell
    void setCastlingRight(Position pos, cell swapableType);

 public:
    Field();
    Field(const Field& field);
    Field& operator=(const Field& field);
    // Create field from saved string (from iternet/load file)
    // Field(const char* saveText);

    //FiguresMoves& operator=(const Field* field);
    //void reset();
};
