#pragma once

#include "pause.hpp"

// Game cycle, where you create server for play using internet
void multiMainServer();

// Function of showing disconect message
inline void showDisconect(){
    switch (language)
    {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Disconect", "Your connection lost, server disconect", app.window);
        break;
    
    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Соединение потеряно", "Соединение потерено, сервер отключён", app.window);
        break;
    }
};

// Function of showing connection normal stop
inline void showStopConnection(){
    switch (language)
    {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Connection stopped", "Connection stopped by another side", app.window);
        break;
    
    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Соединение остановлено", "Соединение остановлено по инициативе второй стороны", app.window);
        break;
    }
}

// Data for internet connection
extern UDPsocket socket;          // Socket to send/recieve data
extern UDPpacket* sendData;       // Packet to send data
extern UDPpacket* recieveData;    // Packet to recieve data

extern timer lastMessageArrive;  // Timer, when last message arrive to control connection
extern timer lastMessageSend;    // Timer, when last message send to control connection
extern bool waitApply;            // Flag of waiting apply message


// Types of internet messages
enum MESSAGE_types{
    MES_INIT = 0,   // Type of starting server and checking compatibility
    MES_START = 1,  // Type of starting new round showing which player start
    MES_NONE = 2,   // Type of nothing for reset connection timer
    MES_TURN = 3,   // Type of setting shape on field, sending to opponent
    MES_STOP = 4,   // Type of closing game and go to menu
    MES_REST = 5,   // Type of restarting game and waiting for new start
    MES_APPL = 6,   // Type of applying, that last message was get
    MES_SKIP = 7    // Type of skipping current round
};

// Types of end of game
enum END_types{
    END_NONE = 0,    // Nothing happen
    END_WIN = 1,     // Current player (first) win game
    END_LOOSE = 2,   // Current player (first) loose game
    END_NOBODY = 3,  // Nobody win game
    END_SKIP = 4     // Game was skipped
};