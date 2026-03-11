/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "fieldSave.hpp"


FieldSave::FieldSave(const Field& _field)
: Field(_field) {
    // Getting current time

}

FieldSave::FieldSave(const char* save) {
    /*resetField();
    // Loading from field from text
    // !
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
    unsigned i=0;
    for (; _saveText[i] && (c < sqr(FIELD_WIDTH)); ++i) {
        switch (_saveText[i]) {
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
            c += _saveText[i] - '0';
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
    for (; _saveText[i]; ++i) {
        switch (_saveText[i]) {
        // Starting player config
        case 'w':
        case 'W':
            state = GameState::CurrentPlay;
            break;

        case 'b':
        case 'B':
            state = GameState::OpponentPlay;
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
    }*/
}

FieldSave::~FieldSave() {

}


const char* FieldSave::getSaveTime() const {

}

const Array<char> FieldSave::getSave() const {

}

char FieldSave::getCheckSum() const {

}
