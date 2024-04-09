
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
                Uint8 textureIndex = IMG_GAME_WHITE_PAWN - 1 + figures[y * FIELD_WIDTH + x];

                // Checking, if figure attackable
                if(figures[y * FIELD_WIDTH + x] > FIG_RED_TYPE){
                    // Changing cell index to normal
                    textureIndex -= FIG_RED_TYPE;

                    // Making it red
                    SDL_SetTextureColorMod(data.textures[textureIndex], 255, 0, 0);

                    // Drawing
                    SDL_RenderCopy(data.renderer, data.textures[textureIndex], NULL, &rect);

                    // Resetting cell color
                    SDL_SetTextureColorMod(data.textures[textureIndex], 0, 0, 0);
                }
                else{
                    SDL_RenderCopy(data.renderer, data.textures[textureIndex], NULL, &rect);
                }
            }
        }
};

// Check, if cell at need position can be attacked
inline bool Board::isAttackable(Uint8 _pos){
    cell c = figures[_pos];
    if(!turn){
        // White turn
        return (c >= FIG_BLACK_PAWN);
    }
    else{
        // Black turn
        return (c < FIG_BLACK_PAWN) && c;
    }
}

// Flag of board, that it was moven
bool wasMoven;

// Try set point, where you can move
inline void Board::tryMove(Sint8 _x, Sint8 _y){
    // Checking getting over border
    if(_y < 0 || _y > FIELD_WIDTH){
        return;
    }
    // Setting new state
    if(figures[_y * FIELD_WIDTH + _x] == FIG_NONE){
        // Setting new position
        figures[_y * FIELD_WIDTH + _x] = FIG_MOVE_TO;
        wasMoven = true;
    }
};

// Try set point, where you can move
inline void Board::tryAttack(Sint8 _x, Sint8 _y){
    // Checking getting over border
    if(_x < 0 || _x > FIELD_WIDTH || _y < 0 || _y > FIELD_WIDTH){
        return;
    }
    if(isAttackable(_y * FIELD_WIDTH + _x)){
        // Setting figure to be attacked
        figures[_y * FIELD_WIDTH + _x] += FIG_RED_TYPE;
        wasMoven = true;
    }
};

// 
inline void Board::setDiagonals(const coord _x, const coord _y){
    // Diagonal to left up
    for(Sint8 x = _x-1; (x >= 0) && (_y - _x + x >= 0); --x){
        // Getting new position
        Uint8 pos = x + (_y - _x + x) * FIELD_WIDTH;
        // Checking on getting on figure
        if(figures[pos]){
            if(isAttackable(pos)){
                figures[pos] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[pos] = FIG_MOVE_TO;
        wasMoven = true;
    }

    // Diagonal to down right
    for(Sint8 x = _x+1; (x < FIELD_WIDTH) && (_y - _x + x < FIELD_WIDTH); ++x){
        // Getting new position
        Uint8 pos = x + (_y - _x + x) * FIELD_WIDTH;
        // Checking on getting on figure
        if(figures[pos]){
            if(isAttackable(pos)){
                figures[pos] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[pos] = FIG_MOVE_TO;
        wasMoven = true;
    }

    // Diagonal to down left
    for(Sint8 x = _x - 1; (x >= 0) && (_y + _x - x < FIELD_WIDTH); --x){
        // Getting new position
        Uint8 pos = x + (_y + _x - x) * FIELD_WIDTH;
        // Checking on getting on figure
        if(figures[pos]){
            if(isAttackable(pos)){
                figures[pos] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[pos] = FIG_MOVE_TO;
        wasMoven = true;
    }

    // Diagonal to up right
    for(Sint8 x = _x + 1; (x < FIELD_WIDTH) && (_y + _x - x >= 0); ++x){
        // Getting new position
        Uint8 pos = x + (_y + _x - x) * FIELD_WIDTH;
        // Checking on getting on figure
        if(figures[pos]){
            if(isAttackable(pos)){
                figures[pos] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[pos] = FIG_MOVE_TO;
        wasMoven = true;
    }
};

// 
inline void Board::setStraight(const coord _x, const coord _y){
    // To left part
    for(Sint8 i = _x-1; i >= 0; --i){
        // Checking on getting on figure
        if(figures[i + _y * FIELD_WIDTH]){
            if(isAttackable(i + _y * FIELD_WIDTH)){
                figures[i + _y * FIELD_WIDTH] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[i + _y * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
    }
    // To right part
    for(Sint8 i = _x+1; i < FIELD_WIDTH; ++i){
        // Checking on getting on figure
        if(figures[i + _y * FIELD_WIDTH]){
            if(isAttackable(i + _y * FIELD_WIDTH)){
                figures[i + _y * FIELD_WIDTH] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[i + _y * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
    }

    // To up part
    for(Sint8 i = _y-1; i >= 0; --i){
        // Checking on getting on figure
        if(figures[_x + i * FIELD_WIDTH]){
            if(isAttackable(_x + i * FIELD_WIDTH)){
                figures[_x + i * FIELD_WIDTH] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[_x + i * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
    }
    // To down part
    for(Sint8 i = _y+1; i < FIELD_WIDTH; ++i){
        // Checking on getting on figure
        if(figures[_x + i * FIELD_WIDTH]){
            if(isAttackable(_x + i * FIELD_WIDTH)){
                figures[_x + i * FIELD_WIDTH] += FIG_RED_TYPE;
                wasMoven = true;
            }
            break;
        }
        // Setting point to move to
        figures[_x + i * FIELD_WIDTH] = FIG_MOVE_TO;
        wasMoven = true;
    }
};

// 
inline void Board::setAround(const coord _x, const coord _y, const Sint8 _moves[][2]){
    // 
    for(Uint8 i=0; i < 8; ++i){
        Sint8 x = _x + _moves[i][0];
        Sint8 y = _y + _moves[i][1];
        // Checking on getting over border
        if( (x >= 0) && (x < FIELD_WIDTH) && (y >= 0) && (y < FIELD_WIDTH)){
            // Checking on free cell
            if(figures[x + y * FIELD_WIDTH] == FIG_NONE){
                figures[x + y * FIELD_WIDTH] = FIG_MOVE_TO;
                wasMoven = true;
            }
            // Checking on attackable cell
            else if(isAttackable(x + y * FIELD_WIDTH)){
                figures[x + y * FIELD_WIDTH] += FIG_RED_TYPE;
                wasMoven = true;
            }
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
                // Basic move
                tryMove(_x, _y - 1);

                // Check, if in start position and wasn't any move
                if(wasMoven && _y == FIELD_WIDTH - 2){
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
                setAround(_x, _y, kingMoves);
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
                // Basic move
                tryMove(_x, _y + 1);

                // Check, if in start position and wasn't any move
                if(wasMoven && _y == 1){
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
                setAround(_x, _y, kingMoves);
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

            // Clearing field after turn (resetting figure move to and red type)
            for(Uint8 i=0; i < fieldSize; ++i){
                // Clear points to move
                if(figures[i] == FIG_MOVE_TO){
                    figures[i] = FIG_NONE;
                }
                // Clearing red figures
                else if(figures[i] > FIG_RED_TYPE){
                    figures[i] -= FIG_RED_TYPE;
                }
            }
            return;
        }
        // Checking, if new position allowable
        else if(figures[_y * FIELD_WIDTH + _x] >= FIG_MOVE_TO){
            // Setting new position to cell
            figures[_y * FIELD_WIDTH + _x] = activeCell.type;
            figures[activeCell.Y * FIELD_WIDTH + activeCell.X] = FIG_NONE;

            // Clearing field after turn (resetting figure move to and red type)
            for(Uint8 i=0; i < fieldSize; ++i){
                // Clear points to move
                if(figures[i] == FIG_MOVE_TO){
                    figures[i] = FIG_NONE;
                }
                // Clearing red figures
                else if(figures[i] > FIG_RED_TYPE){
                    figures[i] -= FIG_RED_TYPE;
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
