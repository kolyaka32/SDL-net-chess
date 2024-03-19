#pragma once

#include "SDL_net.h"

// Data for internet connection
/*extern UDPsocket socket;          // Socket to send/recieve data
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

// Function of showing disconect message
/*inline void showDisconect(){
    switch (language)
    {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Disconect", "Your connection lost, server disconect", window);
        break;
    
    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Соединение потеряно", "Соединение потерено, сервер отключён", window);
        break;
    }
};

// Function of showing connection normal stop
inline void showStopConnection(){
    switch (language)
    {
    case LNG_ENGLISH:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Connection stopped", "Connection stopped by another side", window);
        break;
    
    case LNG_RUSSIAN:
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Соединение остановлено", "Соединение остановлено по инициативе второй стороны", window);
        break;
    }
}

// Macros for removing select from typeBox
#define removeTypeBox() if(inBox){\
    typeBoxes[inBox - 1].removeSelect();\
    inBox = 0; }

// Macros for sending message
inline void send(MESSAGE_types type, Uint8 d1 = 0, Uint8 d2 = 0, Uint8 d3 = 0, Uint8 d4 = 0){
    sendData->data[0] = type;
    sendData->data[1] = d1;
    sendData->data[2] = d2;
    sendData->data[3] = d3;
    sendData->data[4] = d4;
    SDLNet_UDP_Send(socket, -1, sendData);

    lastMessageSend = SDL_GetTicks64();
    waitApply = true;
}*/