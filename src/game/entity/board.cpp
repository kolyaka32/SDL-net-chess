
#include "board.hpp"
#include "../../data/data.hpp"

//
Board::Board(){
    reset();
}

//
Board::~Board(){

}

//
void Board::reset(){
    // Clearing field
    memset(figures, FIG_NONE, fieldSize);
    turn = TURN_WHITE;
    activeCell.type = FIG_NONE;


    // Forsyth–Edwards Notation
    // White figures: pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K"
    // Black figures - "pnbrqk"
    // 1-8 - spaces between figures
    // '\', '/' - lines separator
    // 'w', 'l' - which command start

    // Base notation:
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    // Setting figures on them places by given text
    Uint8 c = 0;  // Counter of placed

    // Parsing text for setting figures
    Uint16 i = 0;
    for(; data.startConfig[i] && (c < fieldSize); ++i){
        switch (data.startConfig[i])
        {
        // Basic white figures
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

        // Basic figures
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
            c += data.startConfig[i] - '0';
            break;

        // Line separator
        case '\\':
        case '/':
            // Checking, if not on another line
            if(c % FIELD_WIDTH){
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
    for(; data.startConfig[i]; ++i){
        switch (data.startConfig[i])
        {
        // Starting player config
        case 'w':
        case 'W':
            turn = TURN_WHITE;
            break;

        case 'b':
        case 'B':
            turn = TURN_BLACK;
            break;

        // Last part with castling (in work)
        // 'k', 'K' 'q', 'Q'

        }
    }
};

// 
void Board::blit() const{
    // Drawing background
    data.setColor({255, 206, 158, 255});
    SDL_RenderClear(data.renderer);

    // Drawing background
    data.setColor({206, 139, 71, 255});
    for(coord y=0; y < FIELD_WIDTH; ++y)
        for(coord x=y%2; x < FIELD_WIDTH; x+=2){
            SDL_Rect rect = {x * CELL_SIDE, y * CELL_SIDE, CELL_SIDE, CELL_SIDE};
            SDL_RenderFillRect(data.renderer, &rect);
        }
    
    // Drawing each figure
    for(Uint8 y=0; y < FIELD_WIDTH; ++y)
        for(coord x=0; x < FIELD_WIDTH; ++x){
            if(figures[y * FIELD_WIDTH + x]){
                SDL_Rect rect = {x * CELL_SIDE, y * CELL_SIDE, CELL_SIDE, CELL_SIDE};
                SDL_RenderCopy(data.renderer, data.textures[IMG_GAME_WHITE_PAWN - 1 + figures[y * FIELD_WIDTH + x]], NULL, &rect);
            }
        }
};

// Flag of board, that it was moven
bool wasMoven;

// Try set point, where you can move
inline void Board::tryMove(Sint8 _x, Sint8 _y){
    // Setting new state
    if(figures[_y * FIELD_WIDTH + _x] == FIG_NONE){
        // Setting new position
        figures[_y * FIELD_WIDTH + _x] = FIG_MOVE_TO;
        wasMoven = true;
    }
    /*
    else if(figures[].isAttacable())
    */
};

// 
inline void Board::setDiagonals(const coord _x, const coord _y){
    Sint8 x = _x - 1;
    // To 0 part
    while((x >= 0) && (figures[x + (_y - _x + x) * FIELD_WIDTH] == FIG_NONE) && (_y - _x + x >= 0)){
        figures[x + (_y - _x + x) * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        x--;
    }
    // To end part
    x = _x + 1;
    while((x < FIELD_WIDTH) && (figures[x + (_y - _x + x) * FIELD_WIDTH] == FIG_NONE) && (_y - _x + x < FIELD_WIDTH)){
        figures[x + (_y - _x + x) * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        x++;
    }
    // Second diagonal
    x = _x - 1;
    // To 0 part
    while((x >= 0) && (figures[x + (_y + _x - x) * FIELD_WIDTH] == FIG_NONE) && (_y + _x - x < FIELD_WIDTH)){
        figures[x + (_y + _x - x) * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        x--;
    }
    // To end part
    x = _x + 1;
    while((x < FIELD_WIDTH) && (figures[x + (_y + _x - x) * FIELD_WIDTH] == FIG_NONE) && (_y + _x - x >= 0)){
        figures[x + (_y + _x - x) * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        x++;
    }
};

// 
inline void Board::setStraight(const coord _x, const coord _y){
    // Left part
    Sint8 i = _x - 1;
    while((i >= 0) && (figures[i + _y * FIELD_WIDTH] == FIG_NONE)){
        figures[i + _y * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        i--;
    }
    // Right part
    i = _x + 1;
    while((i < FIELD_WIDTH) && (figures[i + _y * FIELD_WIDTH] == FIG_NONE)){
        figures[i + _y * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        i++;
    }
    // Upper part
    i = _y - 1;
    while((i >= 0) && (figures[_x + i * FIELD_WIDTH] == FIG_NONE)){
        figures[_x + i * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        i--;
    }
    // Down part
    i = _y + 1;
    while((i < FIELD_WIDTH) && (figures[_x + i * FIELD_WIDTH] == FIG_NONE)){
        figures[_x + i * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
        i++;
    }
};

// 
inline void Board::setAroundKing(const coord _x, const coord _y){
    //
    for(Uint8 i=0; i < 8; ++i){
        Sint8 x = _x + kingMoves[i][0];
        Sint8 y = _y + kingMoves[i][1];
        if( (x >= 0) && (x < FIELD_WIDTH) && (y >= 0) && (y < FIELD_WIDTH) && (figures[x + y * FIELD_WIDTH] == FIG_NONE)){
            figures[x + y * FIELD_WIDTH] = FIG_MOVE_TO;
            wasMoven = true;
        }
    }
};

// 
inline void Board::setAroundKnight(const coord _x, const coord _y){
    //
    for(Uint8 i=0; i < 8; ++i){
        Sint8 x = _x + knightMoves[i][0];
        Sint8 y = _y + knightMoves[i][1];
        if( (x >= 0) && (x < FIELD_WIDTH) && (y >= 0) && (y < FIELD_WIDTH) && (figures[x + y * FIELD_WIDTH] == FIG_NONE)){
            figures[x + y * FIELD_WIDTH] = FIG_MOVE_TO;
            wasMoven = true;
        }
    }
};

// Clicking on field (grab and put figures)
void Board::click(const coord _x, const coord _y){
    if(!activeCell.type){
        // Finding clicked cell and finding new positions
        activeCell.type = figures[_y * FIELD_WIDTH + _x];
        activeCell.X = _x;
        activeCell.Y = _y;

        // Resetting flag
        wasMoven = false;

        // Checking, which color is active
        if(turn == TURN_WHITE){
            // White figures turn
            // Setting positions of cell, where active can go, depend on figure
            switch (activeCell.type)
            {
            case FIG_WHITE_PAWN:
                // Check, if in start position
                if(_y == FIELD_WIDTH - 2){
                    tryMove(_x, _y - 2);
                }
                tryMove(_x, _y - 1);
                break;

            case FIG_WHITE_BISHOP:
                setDiagonals(_x, _y);
                break;

            case FIG_WHITE_ROOK:
                setStraight(_x, _y);
                break;

            case FIG_WHITE_KNIGHT:
                setAroundKnight(_x, _y);
                break;

            case FIG_WHITE_QUEEN:
                setDiagonals(_x, _y);
                setStraight(_x, _y);
                break;
            
            case FIG_WHITE_KING:
                setAroundKing(_x, _y);
                break;
            }
        }
        else
        {
            // Black figures turn
            // Setting positions of cell, where active can go, depend on figure
            switch (activeCell.type)
            {
            case FIG_BLACK_PAWN:
                // Check, if in start position
                if(_y == 1){
                    tryMove(_x, _y + 2);
                }
                tryMove(_x, _y + 1);
                break;

            case FIG_BLACK_BISHOP:
                setDiagonals(_x, _y);
                break;

            case FIG_BLACK_ROOK:
                setStraight(_x, _y);
                break;

            case FIG_BLACK_KNIGHT:
                setAroundKnight(_x, _y);
                break;

            case FIG_BLACK_QUEEN:
                setDiagonals(_x, _y);
                setStraight(_x, _y);
                break;
            
            case FIG_BLACK_KING:
                setAroundKing(_x, _y);
                break;
            }
        }
        // Checking, if wasn't any move
        if(!wasMoven){
            activeCell.type = FIG_NONE;
            return;
        }
    }
    else{
        // Checling, if on old place
        if(activeCell.Y == _y && activeCell.X == _x){
            // Returning to first step
            activeCell.type = FIG_NONE;

            // Clearing field after turn
            for(Uint8 i=0; i < fieldSize; ++i){
                if(figures[i] == FIG_MOVE_TO){
                    figures[i] = FIG_NONE;
                }
            }
            return;
        }
        // Checking, if new position allowable
        else if(figures[_y * FIELD_WIDTH + _x] == FIG_MOVE_TO){
            // Setting new position to cell
            figures[_y * FIELD_WIDTH + _x] = activeCell.type;
            figures[activeCell.Y * FIELD_WIDTH + activeCell.X] = FIG_NONE;

            // Clearing field after turn
            for(Uint8 i=0; i < fieldSize; ++i){
                if(figures[i] == FIG_MOVE_TO){
                    figures[i] = FIG_NONE;
                }
            }

            // Disabling moving cell
            activeCell.type = FIG_NONE;

            // Changing moving player
            if(turn == TURN_WHITE){
                turn = TURN_BLACK;
            }
            else{
                turn = TURN_WHITE;
            }
            return;
        }
    }
};
