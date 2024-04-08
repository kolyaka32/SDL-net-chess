#pragma once

#include "../../define.hpp"
#include "../../dataTypes.hpp"

// Names of all figures in game
enum FIG_names{
    // None-element
    FIG_NONE,

    // Figures
    // White figures
    FIG_WHITE_PAWN,
    FIG_WHITE_BISHOP,
    FIG_WHITE_ROOK,
    FIG_WHITE_KNIGHT,
    FIG_WHITE_QUEEN,
    FIG_WHITE_KING,

    // Black figures
    FIG_BLACK_PAWN,
    FIG_BLACK_BISHOP,
    FIG_BLACK_ROOK,
    FIG_BLACK_KNIGHT,
    FIG_BLACK_QUEEN,
    FIG_BLACK_KING,
    
    // Point, where you can move to
    FIG_MOVE_TO,
};


// Posible coordinats to move
/*Sint8 FiguresMoves[8][8] = {
    // Pawn moves
    {

    }
};*/



// Class of single game figures
/*class FigureTemplate
{
private:
    

protected:
    coord x, y;  // Figure coordinates
public:
    FigureTemplate();
    ~FigureTemplate();

    virtual void checkAcess(coord X, coord Y);

};

*/