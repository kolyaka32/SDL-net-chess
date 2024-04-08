
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
    for(Uint16 i = 0; data.startConfig[i]; ++i){
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
            if(c >= fieldSize){
                return;
            }
            break;

        // Line separator
        case '\\':
        case '/':
            // Checking, if not on another line
            if(c % FIELD_WIDTH){
                // Forced going to next line
                c = ((c-1) / FIELD_WIDTH + 1) * FIELD_WIDTH;
                if(c >= fieldSize){
                    return;
                }
            }
            break;

        // Starting player config
        case 'w':
        case 'W':
            turn = TURN_WHITE;
            break;

        case 'l':
        case 'L':
            turn = TURN_BLACK;
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

//
void Board::click(coord X, coord Y){

};
