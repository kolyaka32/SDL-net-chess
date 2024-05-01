
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
    // Clearing data
    memset(figures, FIG_NONE, fieldSize);  // Resetting all field
    turn = TURN_WHITE;                     // First move from white figures
    activeCell.type = FIG_NONE;            // None cell selected
    castling = 0;                          // All castlings not possible


    // Forsyth–Edwards Notation
    // White figures: pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K"
    // Black figures - "pnbrqk"
    // 1-8 - spaces between figures
    // '\', '/' - lines separator
    // 'w', 'l' - which command start

    // Base notation:
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    // Setting figures on them places by given text
    position c = 0;  // Counter of placed

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
};

// 
void Board::blit() const{
    // Drawing background
    data.setColor({255, 206, 158, 255});
    SDL_RenderClear(data.renderer);

    // Drawing background
    data.setColor({206, 139, 71, 255});
    for(coord y = 0; y < FIELD_WIDTH; ++y)
        for(coord x = y % 2; x < FIELD_WIDTH; x += 2){
            SDL_Rect rect = {x * CELL_SIDE, y * CELL_SIDE, CELL_SIDE, CELL_SIDE};
            SDL_RenderFillRect(data.renderer, &rect);
        }
    
    // Drawing each figure
    for(coord y = 0; y < FIELD_WIDTH; ++y)
        for(coord x = 0; x < FIELD_WIDTH; ++x){
            if(figures[getPos(x, y)]){
                SDL_Rect rect = {x * CELL_SIDE, y * CELL_SIDE, CELL_SIDE, CELL_SIDE};
                Uint8 textureIndex = IMG_GAME_WHITE_PAWN - 1 + figures[getPos(x, y)];

                // Checking, if figure current (blue)
                if(figures[getPos(x, y)] > FIG_BLUE_TYPE){
                    // Changing cell index to normal
                    textureIndex -= FIG_BLUE_TYPE;

                    // Making it blue
                    SDL_SetTextureColorMod(data.textures[textureIndex], 0, 0, 255);

                    // Drawing
                    SDL_RenderCopy(data.renderer, data.textures[textureIndex], NULL, &rect);

                    // Resetting cell color
                    SDL_SetTextureColorMod(data.textures[textureIndex], 0, 0, 0);
                }
                // Checking, if figure attackable (red)
                else if(figures[getPos(x, y)] > FIG_RED_TYPE){
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

// Clicking on field (grab and put figures)
Uint8 Board::click(const coord _x, const coord _y){
    if(!activeCell.type){
        // Finding clicked cell, it position
        activeCell.pos = getPos(_x, _y);
        activeCell.type = figures[activeCell.pos];

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
                // Check castling
                if(castling & CASTLING_W_Q){
                    setCastlingRight(_x, _y, FIG_WHITE_KING);
                }
                if(castling & CASTLING_W_K){
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
                if(castling & CASTLING_W_Q){
                    setCastlingLeft(_x, _y, FIG_WHITE_ROOK);
                }
                if(castling & CASTLING_W_K){
                    setCastlingRight(_x, _y, FIG_WHITE_ROOK);
                }
                // Main move
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
                // Check castling
                if(castling & CASTLING_B_Q){
                    setCastlingRight(_x, _y, FIG_BLACK_KING);
                }
                if(castling & CASTLING_B_K){
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
                if(castling & CASTLING_B_Q){
                    setCastlingLeft(_x, _y, FIG_BLACK_ROOK);
                }
                if(castling & CASTLING_B_K){
                    setCastlingRight(_x, _y, FIG_BLACK_ROOK);
                }
                // Main move
                setAround(_x, _y, kingMoves);
                break;
            }
        }
        // Checking, if wasn't any move
        if(!wasMoven){
            activeCell.type = FIG_NONE;
            return END_NONE;
        }
        // Changing color of current cell
        figures[getPos(_x, _y)] += FIG_BLUE_TYPE;
        return END_NONE;
    }
    else{
        // Checling, if on old place
        if(activeCell.pos == getPos(_x, _y)){
            // Disacting current cell
            figures[getPos(_x, _y)] -= FIG_BLUE_TYPE;

            // Returning to first step
            activeCell.type = FIG_NONE;

            // Clearing field after turn (resetting figure move to and red type)
            for(position i=0; i < fieldSize; ++i){
                // Clear points to move
                if(figures[i] == FIG_MOVE_TO){
                    figures[i] = FIG_NONE;
                }
                // Clearing red figures
                else if(figures[i] > FIG_RED_TYPE){
                    figures[i] -= FIG_RED_TYPE;
                }
            }
            return END_NONE;
        }
        // Checking, if new position allowable
        else if(figures[getPos(_x, _y)] >= FIG_MOVE_TO){
            if(turn == TURN_WHITE){
                // Checking on game end (if there king of another command)
                if(figures[getPos(_x, _y)] == FIG_RED_TYPE + FIG_BLACK_KING){
                    return END_WIN + turn;
                }
                else if(activeCell.type == FIG_WHITE_ROOK){
                    // Disabling posible castling for next turns
                    if(_x < FIELD_WIDTH/2){
                        castling -= CASTLING_W_Q;
                    }
                    else{
                        castling -= CASTLING_W_K;
                    }
                    // Check, if castling
                    if(figures[getPos(_x, _y)] == FIG_WHITE_KING + FIG_RED_TYPE){
                        // Disabling posible castling for next turns
                        castling &= CASTLING_B_Q | CASTLING_B_K;

                        // Swaping figures
                        figures[activeCell.pos] = FIG_WHITE_KING;

                        // Disabling previous cell clearing
                        if(activeCell.pos % FIELD_WIDTH < FIELD_WIDTH/2){
                            activeCell.pos += 1;
                        }
                        else{
                            activeCell.pos -= 1;
                        }
                    }
                }
                else if(activeCell.type == FIG_WHITE_KING){
                    // Disabling posible castling for next turns
                    castling &= CASTLING_B_Q | CASTLING_B_K;

                    // Check, if castling
                    if(figures[getPos(_x, _y)] == FIG_WHITE_ROOK + FIG_RED_TYPE){
                        // Swaping figures
                        figures[activeCell.pos] = FIG_WHITE_ROOK;

                        // Disabling previous cell clearing
                        if(_x < FIELD_WIDTH/2){
                            activeCell.pos -= 1;
                        }
                        else{
                            activeCell.pos += 1;
                        }
                    }
                }
            }
            else{
                // Checking on game end (if there king of another command)
                if(figures[getPos(_x, _y)] == FIG_RED_TYPE + FIG_WHITE_KING){
                    return END_WIN + turn;
                }
                else if(activeCell.type == FIG_BLACK_ROOK){
                    // Disabling posible castling for next turns
                    if(_x < FIELD_WIDTH/2){
                        castling -= CASTLING_B_Q;
                    }
                    else{
                        castling -= CASTLING_B_K;
                    }
                    // Check, if castling
                    if(figures[getPos(_x, _y)] == FIG_BLACK_KING + FIG_RED_TYPE){
                        // Disabling posible castling for next turns
                        castling &= CASTLING_W_Q | CASTLING_W_K;

                        // Swaping figures
                        figures[activeCell.pos] = FIG_BLACK_KING;

                        // Disabling previous cell clearing
                        if(activeCell.pos % FIELD_WIDTH < FIELD_WIDTH/2){
                            activeCell.pos += 1;
                        }
                        else{
                            activeCell.pos -= 1;
                        }
                    }
                }
                else if(activeCell.type == FIG_BLACK_KING){
                    // Disabling posible castling for next turns
                    castling &= CASTLING_W_Q | CASTLING_W_K;

                    // Check, if castling
                    if(figures[getPos(_x, _y)] == FIG_BLACK_ROOK + FIG_RED_TYPE){
                        // Swaping figures
                        figures[activeCell.pos] = FIG_BLACK_ROOK;

                        // Disabling previous cell clearing
                        if(_x < FIELD_WIDTH/2){
                            activeCell.pos -= 1;
                        }
                        else{
                            activeCell.pos += 1;
                        }
                    }
                }
            }

            // Setting new position to cell
            figures[getPos(_x, _y)] = activeCell.type;
            figures[activeCell.pos] = FIG_NONE;

            // Making sound
            data.playSound(SND_TURN);

            // Clearing field after turn (resetting figure move to and red type)
            for(position i=0; i < fieldSize; ++i){
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
            turn = !turn;

            // Shwoing making turn
            return END_TURN;
        }
    }
    return END_NONE;
};


// Making all like in click, but at once and without help
Uint8 Board::move(const coord _x1, const coord _y1, const coord _x2, const coord _y2){
    // Getting current type
    cell currentType = figures[getPos(_x1, _y1)];

    // Checking, which color is active
    if(turn == TURN_WHITE){
        // White figures turn
        // Setting positions of cell, where active can go, depend on figure
        switch (currentType)
        {
        case FIG_WHITE_PAWN:
            // Basic move
            tryMove(_x1, _y1 - 1);

            // Check, if in start position and wasn't any move
            if(wasMoven && _y1 == FIELD_WIDTH - 2){
                tryMove(_x1, _y1 - 2);
            }
            
            // Attack positions
            tryAttack(_x1-1, _y1-1);
            tryAttack(_x1+1, _y1-1);
            break;

        case FIG_WHITE_BISHOP:
            setDiagonals(_x1, _y1);
            break;

        case FIG_WHITE_ROOK:
            // Check castling
            if(castling & CASTLING_W_Q){
                setCastlingRight(_x1, _y1, FIG_WHITE_KING);
            }
            if(castling & CASTLING_W_K){
                setCastlingLeft(_x1, _y1, FIG_WHITE_KING);
            }
            // Main move
            setStraight(_x1, _y1);
            break;

        case FIG_WHITE_KNIGHT:
            setAround(_x1, _y1, knightMoves);
            break;

        case FIG_WHITE_QUEEN:
            setDiagonals(_x1, _y1);
            setStraight(_x1, _y1);
            break;
        
        case FIG_WHITE_KING:
            // Check castling
            if(castling & CASTLING_W_Q){
                setCastlingLeft(_x1, _y1, FIG_WHITE_ROOK);
            }
            if(castling & CASTLING_W_K){
                setCastlingRight(_x1, _y1, FIG_WHITE_ROOK);
            }
            // Main move
            setAround(_x1, _y1, kingMoves);
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
            tryMove(_x1, _y1 + 1);

            // Check, if in start position and wasn't any move
            if(wasMoven && _y1 == 1){
                tryMove(_x1, _y1 + 2);
            }
            
            // Attack positions
            tryAttack(_x1-1, _y1+1);
            tryAttack(_x1+1, _y1+1);
            break;

        case FIG_BLACK_BISHOP:
            setDiagonals(_x1, _y1);
            break;

        case FIG_BLACK_ROOK:
            // Check castling
            if(castling & CASTLING_B_Q){
                setCastlingRight(_x1, _y1, FIG_BLACK_KING);
            }
            if(castling & CASTLING_B_K){
                setCastlingLeft(_x1, _y1, FIG_BLACK_KING);
            }
            // Main move
            setStraight(_x1, _y1);
            break;

        case FIG_BLACK_KNIGHT:
            setAround(_x1, _y1, knightMoves);
            break;

        case FIG_BLACK_QUEEN:
            setDiagonals(_x1, _y1);
            setStraight(_x1, _y1);
            break;
        
        case FIG_BLACK_KING:
            // Check castling
            if(castling & CASTLING_B_Q){
                setCastlingLeft(_x1, _y1, FIG_BLACK_ROOK);
            }
            if(castling & CASTLING_B_K){
                setCastlingRight(_x1, _y1, FIG_BLACK_ROOK);
            }
            // Main move
            setAround(_x1, _y1, kingMoves);
            break;
        }
    }

    // Checking, if get of correct field
    if(figures[getPos(_x2, _y2)] >= FIG_MOVE_TO){
        // Making move
        if(turn == TURN_WHITE){
            // Checking on game end (if there king of another command)
            if(figures[getPos(_x2, _y2)] == FIG_RED_TYPE + FIG_BLACK_KING){
                return END_WIN + turn;
            }
            else if(activeCell.type == FIG_WHITE_ROOK){
                // Disabling posible castling for next turns
                if(_x2 < FIELD_WIDTH/2){
                    castling -= CASTLING_W_Q;
                }
                else{
                    castling -= CASTLING_W_K;
                }
                // Check, if castling
                if(figures[getPos(_x2, _y2)] == FIG_WHITE_KING + FIG_RED_TYPE){
                    // Disabling posible castling for next turns
                    castling &= CASTLING_B_Q | CASTLING_B_K;

                    // Swaping figures
                    figures[activeCell.pos] = FIG_WHITE_KING;

                    // Disabling previous cell clearing
                    if(activeCell.pos % FIELD_WIDTH < FIELD_WIDTH/2){
                        activeCell.pos += 1;
                    }
                    else{
                        activeCell.pos -= 1;
                    }
                }
            }
            else if(activeCell.type == FIG_WHITE_KING){
                // Disabling posible castling for next turns
                castling &= CASTLING_B_Q | CASTLING_B_K;

                // Check, if castling
                if(figures[getPos(_x2, _y2)] == FIG_WHITE_ROOK + FIG_RED_TYPE){
                    // Swaping figures
                    figures[activeCell.pos] = FIG_WHITE_ROOK;

                    // Disabling previous cell clearing
                    if(_x2 < FIELD_WIDTH/2){
                        activeCell.pos -= 1;
                    }
                    else{
                        activeCell.pos += 1;
                    }
                }
            }
        }
        else{
            // Checking on game end (if there king of another command)
            if(figures[getPos(_x2, _y2)] == FIG_RED_TYPE + FIG_WHITE_KING){
                return END_WIN + turn;
            }
            else if(activeCell.type == FIG_BLACK_ROOK){
                // Disabling posible castling for next turns
                if(_x2 < FIELD_WIDTH/2){
                    castling -= CASTLING_B_Q;
                }
                else{
                    castling -= CASTLING_B_K;
                }
                // Check, if castling
                if(figures[getPos(_x2, _y2)] == FIG_BLACK_KING + FIG_RED_TYPE){
                    // Disabling posible castling for next turns
                    castling &= CASTLING_W_Q | CASTLING_W_K;

                    // Swaping figures
                    figures[activeCell.pos] = FIG_BLACK_KING;

                    // Disabling previous cell clearing
                    if(activeCell.pos % FIELD_WIDTH < FIELD_WIDTH/2){
                        activeCell.pos += 1;
                    }
                    else{
                        activeCell.pos -= 1;
                    }
                }
            }
            else if(activeCell.type == FIG_BLACK_KING){
                // Disabling posible castling for next turns
                castling &= CASTLING_W_Q | CASTLING_W_K;

                // Check, if castling
                if(figures[getPos(_x2, _y2)] == FIG_BLACK_ROOK + FIG_RED_TYPE){
                    // Swaping figures
                    figures[activeCell.pos] = FIG_BLACK_ROOK;

                    // Disabling previous cell clearing
                    if(_x2 < FIELD_WIDTH/2){
                        activeCell.pos -= 1;
                    }
                    else{
                        activeCell.pos += 1;
                    }
                }
            }
        }

        // Setting new position to cell
        figures[getPos(_x2, _y2)] = activeCell.type;
        figures[activeCell.pos] = FIG_NONE;

        // Making sound
        data.playSound(SND_TURN);

        // Clearing field after turn (resetting figure move to and red type)
        for(position i=0; i < fieldSize; ++i){
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
        turn = !turn;
    }
    return END_NONE;
}

//
position Board::getPreviousTurn(){
    return activeCell.pos;
}
