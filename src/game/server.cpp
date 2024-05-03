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
    // Code of start connection with other side
    case MES_INIT:
        // Checking, if need start
        if(waitStart){
            // Setting sender address to place, where was send from
            sendData->address = recieveData->address;

            // Sending init message
            send(MES_INIT);

            // Setting flag of connection to start game
            waitStart = false;

            // Starting playing main theme
            data.playMusic(MUS_MAIN_THEME);

            // Updating times of last sended messages
            lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
            lastMessageSend = SDL_GetTicks64() + MESSAGE_NULL_TIMEOUT;
        }
        return 0;

    // Code of turn of another player
    case MES_TURN:
        // Checking, if current turn of another player
        if(waitTurn && endState <= END_TURN){
            // Making opponent turn
            endState = board.move(recieveData->data[1] % FIELD_WIDTH, recieveData->data[1] / FIELD_WIDTH, 
                recieveData->data[2] % FIELD_WIDTH, recieveData->data[2] / FIELD_WIDTH);
            
            // Checking, if there was a move
            if(endState){
                // Allowing current player to move
                waitTurn = false;
            }
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
        if(endState <= END_TURN){
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
                    
                    // Changing turn
                    waitTurn = true;
                }
            }
        }
        else{
            // Getting buttons clicks
            // Game restart
            if(data.textButtons[BTN_GAME_RESTART].in(mouseX, mouseY)){
                // Resetting flags
                endState = END_NONE;
                waitTurn = false;

                // Resetting field
                board.reset();

                // Sending reset flag
                send(MES_REST);

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
        if(endState > END_TURN){
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
