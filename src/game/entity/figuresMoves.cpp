#include "board.hpp"


// Check, if cell at need position can be attacked
bool Board::isAttackable(const position _pos){
    cell c = figures[_pos];
    if(turn == TURN_WHITE){
        // White turn
        return (c >= FIG_BLACK_PAWN);
    }
    else{
        // Black turn
        return (c < FIG_BLACK_PAWN) && c;
    }
}

// Try set point, where you can move
void Board::tryMove(Sint8 _x, Sint8 _y){
    // Checking getting over border
    if(_y < 0 || _y > FIELD_WIDTH){
        return;
    }
    // Setting new state
    if(figures[getPos(_x, _y)] == FIG_NONE){
        // Setting new position
        figures[getPos(_x, _y)] = FIG_MOVE_TO;
        wasMoven = true;
    }
};

// Try set point, where you can move
void Board::tryAttack(Sint8 _x, Sint8 _y){
    // Checking getting over border
    if(_x < 0 || _x > FIELD_WIDTH || _y < 0 || _y > FIELD_WIDTH){
        return;
    }
    if(isAttackable(getPos(_x, _y))){
        // Setting figure to be attacked
        figures[getPos(_x, _y)] += FIG_RED_TYPE;
        wasMoven = true;
    }
};

//
bool Board::tryMoveTo(const position pos){
    // Checking on getting on figure
    if(figures[pos]){
        // Checking, if that figure attackable (in opposite command)
        if(isAttackable(pos)){
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
};

// 
void Board::setDiagonals(const coord _x, const coord _y){
    // Diagonal to left up
    for(Sint8 x = _x-1; (x >= 0) && (_y - _x + x >= 0); --x){
        if(tryMoveTo(getPos(x, _y - _x + x))){
            break;
        }
    }

    // Diagonal to down right
    for(coord x = _x+1; (x < FIELD_WIDTH) && (_y - _x + x < FIELD_WIDTH); ++x){
        if(tryMoveTo(getPos(x, _y - _x + x))){
            break;
        }
    }

    // Diagonal to down left
    for(Sint8 x = _x - 1; (x >= 0) && (_y + _x - x < FIELD_WIDTH); --x){
        if(tryMoveTo(getPos(x, _y + _x - x))){
            break;
        }
    }

    // Diagonal to up right
    for(coord x = _x + 1; (x < FIELD_WIDTH) && (_y + _x - x >= 0); ++x){
        if(tryMoveTo(getPos(x, _y + _x - x))){
            break;
        }
    }
};

// 
void Board::setStraight(const coord _x, const coord _y){
    // To left part
    for(Sint8 i = _x-1; i >= 0; --i){
        if(tryMoveTo(getPos(i, _y))){
            break;
        }
    }

    // To right part
    for(coord i = _x+1; i < FIELD_WIDTH; ++i){
        if(tryMoveTo(getPos(i, _y))){
            break;
        }
    }

    // To up part
    for(Sint8 i = _y-1; i >= 0; --i){
        if(tryMoveTo(getPos(_x, i))){
            break;
        }
    }

    // To down part
    for(coord i = _y+1; i < FIELD_WIDTH; ++i){
        if(tryMoveTo(getPos(_x, i))){
            break;
        }
    }
};

// 
void Board::setAround(const coord _x, const coord _y, const Sint8 _moves[][2]){
    // 
    for(Uint8 i=0; i < 8; ++i){
        Sint8 x = _x + _moves[i][0];
        Sint8 y = _y + _moves[i][1];
        // Checking on getting over border
        if( (x >= 0) && (x < FIELD_WIDTH) && (y >= 0) && (y < FIELD_WIDTH)){
            // Checking on free cell
            if(figures[getPos(x, y)] == FIG_NONE){
                figures[getPos(x, y)] = FIG_MOVE_TO;
                wasMoven = true;
            }
            // Checking on attackable cell
            else if(isAttackable(getPos(x, y))){
                figures[getPos(x, y)] += FIG_RED_TYPE;
                wasMoven = true;
            }
        }
    }
};
