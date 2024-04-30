#include "server.hpp"


//
ServerGameCycle::ServerGameCycle()
{

}

//
ServerGameCycle::~ServerGameCycle()
{

}

//
Uint8 ServerGameCycle::getData(){
    //
    switch (recieveData->data[0])
    {
    // Code of closing game - going to menu
    case MES_STOP:
        showStopConnection();
        return 1;
    
    // Code of applaying last message
    case MES_APPL:
        waitApply = false;
        return 0;

    // Code of unused/strange message
    default:
        return 0;
    }
}


// Global multiplayer variables
/*Uint8 gameState;           // State of game (from END_types)
bool waitTurn;             // Flag of waiting, until another user have his turn
bool runGame;              // Flag of running main game cycle
bool start;                // Flag of showing welcome screen with choosing command


// Waiting menu
static inline Uint8 waitingMenu(){


    // Waiting, when client connect this server
    while(waiting)
    {
        while( SDL_PollEvent(&event) != 0 ){

        }
        // Getting messages from client
        if(SDLNet_UDP_Recv(socket, recieveData) == 1){
            sendData = SDLNet_AllocPacket(INTERNET_BUFFER);
            sendData->address = recieveData->address;
            sendData->len = INTERNET_BUFFER;
            
            // Exiting cycle
            return 0;
        }

    }
    return 0;
}


// Menu for waiting to restart or go to menu
static inline void stopMenu(){

    }

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
          
    }
    // Clearing data
    gameState = END_NONE;
}

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


        // Checking end of game
        if(gameState){
            stopMenu();
        }

    }
    
}

void multiMainServer(){


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

}
*/