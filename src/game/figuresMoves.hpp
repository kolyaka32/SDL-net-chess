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
class FiguresMoves {
 protected:
    // Data for moves
    cell figures[sqr(FIELD_WIDTH)];  // Array of figures on field
    // Flag of current game state
    GameState state;
    // Data of all now posible varhishes
    Uint8 castling;
    // Flag of board, that it was moven
    bool wasMoven;

    // Data for save/load
    SDL_Time saveTime;

    // Functions for interact with board
    void resetField();  // Reset field parametrs
    // Check, if cell at need position can be attacked
    bool isAttackable(position pos);
    // Try set point, where you can move
    bool tryMoveTo(position pos);
    // Set points, where you can move or attack
    void tryMove(Sint8 X, Sint8 Y);
    // Try set point, where you can move
    void tryAttack(Sint8 X, Sint8 Y);
    // Set all cells at diagonals for movable target
    void setDiagonals(coord _x, coord _y);
    // Set all cells at straight lines for movable target
    void setStraight(coord _x, coord _y);
    // Set all cells from array for place, where you can move
    void setAround(coord _x, coord _y, const Sint8 pos[][2]);
    void setCastlingLeft(coord _x, coord _y, cell need);
    void setCastlingRight(coord _x, coord _y, cell need);

 public:
    FiguresMoves();
    FiguresMoves(const FiguresMoves& field);
    // Create field from saved string (from iternet/load file)
    FiguresMoves(const char* saveText);
    // Save this field to text file
    const char* getSaveTime() const;
    // Save system
    void updateSaveInfo();
    const Array<char> getSave() const;
    char getCheckSum() const;
    static int getSaveSize(int width);
    //FiguresMoves& operator=(const Field* field);
    //void reset();
};
