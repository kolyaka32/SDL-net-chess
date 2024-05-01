#include "server.hpp"


//
ServerGameCycle::ServerGameCycle()
{
    // Updating text of created port
    data.texts[TXT_SERVER_PORT].updateText(serverPort);

    // Allowing internet to start
    gettingMutex.unlock();
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
    // Code of initialasing connection
    case MES_START:
    case MES_REST:
        // Resetting field
        board.reset();
        endState = END_NONE;

        // Resetting flag of current actor
        waitTurn = false;

        return 0;

    // Code of turn of another player
    case MES_TURN:
        // Checking, if current turn of another player
        if(waitTurn && endState == END_NONE){
            // Making opponent turn
            endState = board.move(recieveData->data[1] % FIELD_WIDTH, recieveData->data[1] / FIELD_WIDTH, 
                recieveData->data[2] % FIELD_WIDTH, recieveData->data[2] / FIELD_WIDTH);
        }
        return 0;

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


//
Uint8 ServerGameCycle::mouseInput(){
    // Different draw variants
    if(waitStart){
        // Connecting menu
        // Check on connect cancel
        if(data.textButtons[BTN_GAME_CANCEL].in(mouseX, mouseY)){
            // Closing connection
            return 1;
        }
    }
    else{
        // Game variant
        // Pause button
        /*if(settingButton.in(mouseX, mouseY)){
            return 1;
        }*/

        // Clicking on field if possible
        if(endState == END_NONE){
            // Checking, if current turn this player
            if(!waitTurn){
                // Getting previous click
                position previousPos = board.getPreviousTurn();

                // Normal clicking on field
                endState = board.click(mouseX / CELL_SIDE, mouseY / CELL_SIDE);

                // Checking, if need send move
                if(endState){
                    // Sedning turn
                    send(MES_TURN, previousPos, getPos(mouseX / CELL_SIDE, mouseY / CELL_SIDE));
                }
                // Changing turn
                waitTurn = true;
            }
        }
        else{
            // Getting buttons clicks
            // Game restart
            if(data.textButtons[BTN_GAME_RESTART].in(mouseX, mouseY)){
                // Restarting game
                endState = END_NONE;

                // Resetting field
                board.reset();

                // Making sound
                data.playSound(SND_RESET);
            }
            // Going to menu
            else if(data.textButtons[BTN_GAME_MENU].in(mouseX, mouseY)){
                return 1;
            }
        }
    }
    return 0;
};

//
void ServerGameCycle::draw() const{
    // Different draw variants
    if(waitStart){
        // Connecting menu
        // Drawing background
        data.setColor(BLACK);
        SDL_RenderClear(data.renderer);

        // Draw text plates
        data.texts[TXT_SERVER_WAIT].blit();
        data.texts[TXT_SERVER_PORT].blit();
        data.textButtons[BTN_GAME_CANCEL].blit();

        // Rendering at screen
        data.render();
    }
    else{
        // Game variant
        // Bliting field
        board.blit();

        // Bliting game state, if need
        if(endState != END_NONE){
            // Bliting end background
            endBackplate.blit();

            // Bliting text with end state
            switch (endState)
            {
            case END_WIN:
                data.texts[TXT_END_WIN].blit();
                break;
            
            case END_LOOSE:
                data.texts[TXT_END_LOOSE].blit();
                break;
            
            case END_NOBODY:
                data.texts[TXT_END_NOBODY].blit();
                break;
            }

            // Blitting buttons
            data.textButtons[BTN_GAME_RESTART].blit();
            data.textButtons[BTN_GAME_MENU].blit();
        }

        // Bliting all to screen
        data.render();
    }
};

//
void ServerGameCycle::initConnection(){
    // Sending init message
    send(MES_INIT);

    // Setting flag of connection to start game
    waitStart = false;
};

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