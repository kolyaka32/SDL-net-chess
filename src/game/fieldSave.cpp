/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "fieldSave.hpp"


FieldSave::FieldSave(const Field& _field)
: Field(_field) {
    // Getting current time
    SDL_GetCurrentTime(&saveTime);
}

FieldSave::FieldSave(const char* _save) {
    resetField();

    // Loading field from text
    // Forsyth–Edwards Notation
    // White figures: pawn = "P", knight = "N", bishop = "B", rook = "R", queen = "Q" and king = "K"
    // Black figures - "pnbrqk"
    // 1-8 - spaces between figures
    // '\', '/' - lines separator
    // 'w', 'l' - which command start
    // KQkq - is castling on specified side and command is allowed

    // Base notation:
    // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

    // Setting figures on them places by given text
    position c = 0;  // Counter of place on field

    // Parsing text for setting figures
    unsigned i=0;
    for (; _save[i] && (c < sqr(FIELD_WIDTH)); ++i) {
        switch (_save[i]) {
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
            c += _save[i] - '0';
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
    for (; _save[i]; ++i) {
        switch (_save[i]) {
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
    }
    // Getting current time
    SDL_GetCurrentTime(&saveTime);
}

const char* FieldSave::getSaveTime() const {
    // Get local time in date/time format
    SDL_DateTime time;
    SDL_TimeToDateTime(saveTime, &time, true);
    // Get region specific format
    SDL_DateFormat dateFormat;
    SDL_TimeFormat timeFormat;
    SDL_GetDateTimeLocalePreferences(&dateFormat, &timeFormat);
    // Creating string with date-time
    static char buffer[22];
    // Writing date
    switch (dateFormat) {
    case SDL_DATE_FORMAT_YYYYMMDD:
        SDL_snprintf(buffer, 11, "%04d.%02d.%02d",
            time.year, time.month, time.day);
        break;

    case SDL_DATE_FORMAT_DDMMYYYY:
        SDL_snprintf(buffer, 11, "%02d.%02d.%04d",
            time.day, time.month, time.year);
        break;

    case SDL_DATE_FORMAT_MMDDYYYY:
        SDL_snprintf(buffer, 11, "%02d.%02d.%04d",
            time.year, time.month, time.day);
        break;
    }
    // Writing time
    switch (timeFormat) {
    case SDL_TIME_FORMAT_24HR:
        SDL_snprintf(buffer+10, sizeof(buffer)-10, " %02d:%02d:%02d",
            time.hour, time.minute, time.second);
        break;

    case SDL_TIME_FORMAT_12HR:
        if (time.hour < 12) {
            SDL_snprintf(buffer+10, sizeof(buffer)-10, " %02dAM:%02d:%02d",
                time.hour, time.minute, time.second);
        } else {
            SDL_snprintf(buffer+10, sizeof(buffer)-10, " %02dPM:%02d:%02d",
                time.hour, time.minute, time.second);
        }
        break;
    }
    return buffer;
}

const char* FieldSave::getSave() const {
    // Buffer with field and it additional information
    static char buffer[95];
    // Current writing position
    unsigned pos = 0;
    // Writing system data
    buffer[pos++] = getCheckSum();  // Checksum for test of correction

    // Writing time of creation
    Uint64 time = saveTime;
    for (int i=1; i < 17; ++i) {
        buffer[pos++] = time & 0xFF + '0';
        time = time >> 4;
    }

    // ! should be optimised to fit better (write straight bits)
    for (int i=0; i < sqr(FIELD_WIDTH); ++i) {
        switch (figures[i] & 0xFF) {
        case FIG_WHITE_KING:
            buffer[pos++] = 'K';
            break;

        case FIG_WHITE_QUEEN:
            buffer[pos++] = 'Q';
            break;

        case FIG_WHITE_ROOK:
            buffer[pos++] = 'R';
            break;

        case FIG_WHITE_BISHOP:
            buffer[pos++] = 'B';
            break;

        case FIG_WHITE_KNIGHT:
            buffer[pos++] = 'N';
            break;

        case FIG_WHITE_PAWN:
            buffer[pos++] = 'P';
            break;

        // Black figures
        case FIG_BLACK_KING:
            buffer[pos++] = 'k';
            break;

        case FIG_BLACK_QUEEN:
            buffer[pos++] = 'q';
            break;

        case FIG_BLACK_ROOK:
            buffer[pos++] = 'r';
            break;

        case FIG_BLACK_BISHOP:
            buffer[pos++] = 'b';
            break;

        case FIG_BLACK_KNIGHT:
            buffer[pos++] = 'n';
            break;

        case FIG_BLACK_PAWN:
            buffer[pos++] = 'p';
            break;

        case FIG_NONE:
            // In case of empty cell
            // Check - if previous also empty
            if (buffer[pos] < '9' && buffer[pos] >= '0') {
                // Adding to it
                buffer[pos]++;
            } else {
                buffer[pos++] = '1';
            }
            break;
        
        default:
            break;
        }
        // Adding line separator
        if (i%8 == 7) {
            buffer[pos++] = '/';
        }
    }
    // Writing game state (white/black)
    buffer[17+64] = ' ';
    switch (state) {
    case GameState::CurrentPlay:
    case GameState::CurrentWin:
        buffer[17+64+1] = 'w';
        break;

    case GameState::OpponentPlay:
    case GameState::OpponentWin:
        buffer[17+64+1] = 'l';
        break;

    default:
        buffer[17+64+1] = 'w';
        break;
    }
    // Writing castlings
    buffer[pos++] = ' ';
    if (castling & CASTLING_W_K) {
        buffer[pos++] = 'K';
    }
    if (castling & CASTLING_W_Q) {
        buffer[pos++] = 'Q';
    }
    if (castling & CASTLING_B_K) {
        buffer[pos++] = 'k';
    }
    if (castling & CASTLING_B_Q) {
        buffer[pos++] = 'q';
    }
    // Adding end null
    buffer[pos] = '\0';

    return buffer;
}

char FieldSave::getCheckSum() const {
    // Summing all numbers with arbitrary numbers
    char sum = (char)saveTime + (char)state;
    for (int i=0; i < sqr(FIELD_WIDTH); ++i) {
        sum += (char)figures[i];
    }
    return sum;
}
