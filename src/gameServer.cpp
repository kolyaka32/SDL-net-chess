#include "include.hpp"
#include "SDL_net.h"
#include "define.hpp"
#include "values.hpp"
#include "pause.hpp"
#include "gameSingle.hpp"
#include "gameServer.hpp"


// Global multiplayer variables
Uint8 gameState;           // State of game (from END_types)
bool waitTurn;             // Flag of waiting, until another user have his turn
bool runGame;              // Flag of running main game cycle
bool start;                // Flag of showing welcome screen with choosing command

// Data for internet connection
UDPsocket socket;          // Socket to send/recieve data
UDPpacket* sendData;       // Packet to send data
UDPpacket* recieveData;    // Packet to recieve data

timer lastMessageArrive;  // Timer, when last message arrive to control connection
timer lastMessageSend;    // Timer, when last message send to control connection
bool waitApply;            // Flag of waiting apply message


// Waiting menu
static inline Uint8 waitingMenu(){
    // Creating button to exit waiting
    GUI::Button menuButton = {0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU};
    menuButton.init();

    // Variables for waiting cycle
    SDL_Event event;
    bool waiting = true;

    // Waiting, when client connect this server
    while(waiting)
    {
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return 1;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                if(menuButton.in(MouseX, MouseY)){
                    runGame = false;  // Go to menu button
                    return 2;
                }
                break;
            }
        }
        // Getting messages from client
        if(SDLNet_UDP_Recv(socket, recieveData) == 1){
            sendData = SDLNet_AllocPacket(INTERNET_BUFFER);
            sendData->address = recieveData->address;
            sendData->len = INTERNET_BUFFER;
            
            // Exiting cycle
            return 0;
        }

        // Drawing
        SDL_RenderClear(app.renderer);

        // Showing text to wait to connect
        texts[TXT_SERVER_WAIT].blit();
        texts[TXT_SERVER_PORT].blit();

        menuButton.blit();

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);
    }
    return 0;
}

// Macros for sending message
static inline void send(MESSAGE_types type, Uint8 d1 = 0, Uint8 d2 = 0){
    sendData->data[0] = type;
    sendData->data[1] = d1;
    sendData->data[2] = d2;
    SDLNet_UDP_Send(socket, -1, sendData);

    lastMessageSend = SDL_GetTicks64();
    waitApply = true;
}

// Menu for waiting to restart or go to menu
static inline void stopMenu(){
    // Creating buttons
    GUI::Button stopButtons[] = {
        {0.5, 0.7, IMG_MENU_BUTTON, texts + TXT_STOP_RESTART},
        {0.5, 0.9, IMG_MENU_BUTTON, texts + TXT_STOP_MENU}
    };
    for(Uint8 i=0; i < 2; ++i){
        stopButtons[i].init();
    }

    // Starting Internal loop of waiting for restart/go to menu
    bool waiting = true;
    start = true;
    SDL_Event event;
    while(waiting){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                if(stopButtons[0].in(MouseX, MouseY)){  // Restart button
                    // Restarting round
                    field.reset();
                    start = true;
                    waiting = false;

                    // Sending data of restart to client
                    send(MES_REST);
                    break;
                }
                else if(stopButtons[1].in(MouseX, MouseY)){  // Go menu button
                    // Going to menu
                    runGame = false;
                    return;
                }
                break;
            }
        }
        // Checking, if need to send NULL-message
        if(SDL_GetTicks64() > lastMessageSend + MESSAGE_NULL_TIMEOUT){
            send(MES_NONE);
        }
        // Checking, if message wasn't delivered
        if(waitApply && (SDL_GetTicks64() > lastMessageSend + MESSAGE_APPLY_TIMEOUT)){
            // Repeat sending
            SDLNet_UDP_Send(socket, -1, sendData);
        }
        // Checking get data
        if(SDLNet_UDP_Recv(socket, recieveData)){
            switch (recieveData->data[0])
            {
            case MES_STOP:
                // Code of closing game - going to menu
                runGame = false;
                showStopConnection();
                break;
            };
            lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
        }
        else{
            if(SDL_GetTicks64() > lastMessageArrive){
                // Something wrong with connection
                showDisconect();
                runGame = false;
                return;
            }
        }

        // Drawing
        SDL_RenderClear(app.renderer);

        // Showing end message
        texts[TXT_STOP_WIN - 1 + gameState].blit();
        
        // Showing buttons
        for(Uint8 i=0; i < 2; ++i){
            stopButtons[i].blit();
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer);

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    // Clearing data
    gameState = END_NONE;
}

// Main game cycle
static inline void gameCycle(){
    // Creating start buttons
    GUI::Button queueButton[] = {
        {0.25, 0.5, IMG_GREEN_CROSS},
        {0.75, 0.5, IMG_GREEN_CIRCLE}
    };
    // Initialasing buttons
    for(Uint8 i=0; i < 2; ++i){
        queueButton[i].init();
    }

    // Clearing field
    SDL_Event event;
    field.reset();
    start = true;

    // Resetting message timeout
    lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
    lastMessageSend = SDL_GetTicks64() + MESSAGE_NULL_TIMEOUT;

    // Activating main cycle
    while(runGame){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return;

            case SDL_KEYDOWN:
                // Checking for restart key
                switch (event.key.keysym.sym)
                {
                case SDLK_r:
                    // Skipping game
                    gameState = END_SKIP;
                    send(MES_SKIP);
                    break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                if(start){
                    if(queueButton[0].in(MouseX, MouseY)){
                        // Activation cross - moving first
                        player = queue = 0;
                        waitTurn = false;
                        start = false;
                    }
                    else if(queueButton[1].in(MouseX, MouseY)){
                        // Activating circle - moving second
                        player = queue = 1;
                        waitTurn = true;
                        start = false;
                    }
                    // Sending message to client of start
                    send(MES_START, queue);
                }
                else if(!waitTurn && field.clickMulti(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR))){
                    // Sending data to another player
                    send(MES_TURN, MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR));
                    waitTurn = true;
                }
                break;
            }
        }
        // Checking, if need to send NULL-message
        if(SDL_GetTicks64() > lastMessageSend + MESSAGE_NULL_TIMEOUT){
            send(MES_NONE);
        }
        // Checking, if message wasn't delivered
        if(waitApply && (SDL_GetTicks64() > lastMessageSend + MESSAGE_APPLY_TIMEOUT)){
            // Repeat sending
            SDLNet_UDP_Send(socket, -1, sendData);
        }
        // Checking get data
        if(SDLNet_UDP_Recv(socket, recieveData)){
            lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
            switch (recieveData->data[0])
            {
            case MES_TURN: 
                // Code of opponent placing shape
                if(!start){
                    field.clickTwo(recieveData->data[1], recieveData->data[2]);
                    // Allow to current user to make turn
                    waitTurn = false;
                }
                break;
            
            case MES_STOP:
                // Code of closing game - going to menu
                runGame = false;
                showStopConnection();
                return;

            case MES_APPL:
                // Last send message arrive normaly
                waitApply = false;
                break;
            };
        }
        else{
            if(SDL_GetTicks64() > lastMessageArrive){
                // Something wrong with connection
                showDisconect();
                runGame = false;
                return;
            }
        };

        // Checking end of game
        if(gameState){
            stopMenu();
        }

        // Drawing
        SDL_RenderClear(app.renderer);
        
        field.blit();

        // Showing game chose
        if(start){
            // Showing text for Activation
            texts[TXT_START_SELECT].blit();
            // Showing buttons for chose
            for(Uint8 i=0; i < 2; ++i){
                queueButton[i].blit();
            }
        }
        else{
            if(waitTurn){
                texts[TXT_INTERNET_WAIT].blit();
            }
            else{
                texts[TXT_INTERNET_TURN].blit();
            }
        }

        // Blitting textures on screen
        SDL_RenderPresent(app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    // Sending message of server disabling
    send(MES_STOP);
}

void multiMainServer(){
    // Setting base port to show next
    Uint16 port = BASE_PORT;
    
    // Openning UDP port to recieve data from client
    while(!(socket = SDLNet_UDP_Open(port))){
        // Checking, if not open port - setting random 
        port = rand() % 4000;
    }
    // Simulated packet loss for packets for better testing
    #if DEBUG
    SDLNet_UDP_SetPacketLoss(socket, CONNECTION_LOST_PERCENT);
    #endif

    // Allocating memory to send and recieve packets
    recieveData = SDLNet_AllocPacket(INTERNET_BUFFER);

    // Updating text with port to show it
    texts[TXT_SERVER_PORT].updateText(port);

    runGame = true;

    // Starting cycle for waiting to connect
    if(waitingMenu()){
        // Going to main game menu
        // Clearing recieve socket
        SDLNet_UDP_Close(socket);
        SDLNet_FreePacket(recieveData);
        return;
    }

    // Sending initialasing message with need field widthes
    send(MES_INIT, fieldWidth, winWidth);

    // Starting main game cycle
    gameCycle();

    // Closing port
    SDLNet_UDP_Close(socket);
    SDLNet_FreePacket(recieveData);
    SDLNet_FreePacket(sendData);
}
