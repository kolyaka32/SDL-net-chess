#include "client.hpp"

//
ClientGameCycle::ClientGameCycle()
{
    // Allowing internet to start
    gettingMutex.unlock();
}

//
ClientGameCycle::~ClientGameCycle()
{
    // Additional stopping text input on case, when was closed at inputting
    removeSelection();

    // Starting playing menu theme if need
    if(!waitStart){
        data.playMusic(MUS_MENU_THEME);
    }
}

// Macros for removing select from typeBox
void ClientGameCycle::removeSelection(){
    if(selectedBox){
        typeBoxes[selectedBox - 1].removeSelect();
        selectedBox = 0;
    }
}

//
Uint8 ClientGameCycle::getData(){
    //
    switch (recieveData->data[0])
    {
    // Code of initialasing connection
    case MES_INIT:
        // Checking, if get first init message
        if(waitStart){
            // Starting playing main theme
            data.playMusic(MUS_MAIN_THEME);

            // Setting flag of connection to start game
            waitStart = false;

            // Updating times of last sended messages
            lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
            lastMessageSend = SDL_GetTicks64() + MESSAGE_NULL_TIMEOUT;
        }

        return 0;
    
    // Code of starting game
    case MES_START:
    case MES_REST:
        // Resetting field
        board.reset();
        endState = END_NONE;

        // Resetting flag of current player
        waitTurn = true;

        return 0;

    // Code of turn of another player
    case MES_TURN:
        // Checking, if current turn of another player
        if(waitTurn && endState <= END_TURN){
            // Making opponent turn
            endState = board.move(recieveData->data[1] % FIELD_WIDTH, recieveData->data[1] / FIELD_WIDTH, 
                recieveData->data[2] % FIELD_WIDTH, recieveData->data[2] / FIELD_WIDTH);

            // Allowing current player to move
            if(endState){
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
void ClientGameCycle::getInput(){
    SDL_Event event;
    while(running){
        while( SDL_PollEvent(&event) != 0 ){
            // Checking on game variant
            if(waitStart){
                // Entering data variant
                switch (event.type)
                {
                case SDL_QUIT:
                    data.running = false;
                    return;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        removeSelection();
                        break;
                    
                    case SDLK_RETURN:
                    case SDLK_RETURN2:
                    case SDLK_KP_ENTER:
                        removeSelection();
                        // Trying connect at address
                        tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer);
                        break;
                    
                    default:
                        if(selectedBox){
                            typeBoxes[selectedBox - 1].press(event.key.keysym.sym);
                        }
                    }
                    break;

                case SDL_TEXTINPUT:
                    // Typing text on which object is selected
                    if(selectedBox){
                        typeBoxes[selectedBox - 1].writeString(event.text.text, false);
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    // Getting mouse position
                    SDL_GetMouseState(&mouseX, &mouseY);

                    // Getting mouse press
                    if(mouseInput()){
                        return;
                    }
                    break;
                }
            }
            else{
                // Main game cycle
                switch (event.type)
                {
                case SDL_QUIT:
                    data.running = false;
                    return;

                case SDL_KEYDOWN:
                    // Switching between keys
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        // Clearing selection by escape
                        board.resetSelection();
                        break;
                        
                    case SDLK_q:
                        // Quiting to menu
                        return;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    // Getting mouse position
                    SDL_GetMouseState(&mouseX, &mouseY);

                    // Getting mouse press
                    if(mouseInput()){
                        return;
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    //LMBclick = false;
                    selectedBox = 0;
                    break;
                }
            }
        }
        // Check, if entering text and need to blink caret in type box
        if(waitStart && selectedBox && (SDL_GetTicks64() > lastTypeBoxUpdate)){
            // Updating type box for show place to type
            typeBoxes[selectedBox - 1].updateCaret();
            lastTypeBoxUpdate = SDL_GetTicks64() + 500;
        }
        // Waiting next cycle
        inputTimer.sleep();
    }
};


//
Uint8 ClientGameCycle::mouseInput(){
    // Different draw variants
    if(waitStart){
        // Connecting menu
        // Connect to server button
        if(data.textButtons[BTN_GAME_CONNECT].in(mouseX, mouseY)){
            removeSelection();
            // Trying connect at address
            tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer);
            return 0;
        }
        // Return to menu button
        else if(data.textButtons[BTN_GAME_CANCEL].in(mouseX, mouseY)){
            // Returning to menu
            removeSelection();
            return 1;
        }
        // Selecting need box
        for(Uint8 i=0; i < 2; ++i){
            // Checking, if click on that box
            if(typeBoxes[i].in(mouseX, mouseY)){
                // Checking, if box not selected
                if(selectedBox != i+1){
                    selectedBox = i+1;
                    typeBoxes[i].select();
                    lastTypeBoxUpdate = SDL_GetTicks64() + 700;
                }
                return 0;
            }
        }
        // If press on somewhere else on field - resetting selection
        removeSelection();
        return 0;
    }
    else{
        // Game variantwaitTurn = true;
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
                endState = board.click((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE);

                // Checking, if need send move
                if(endState){
                    // Sending turn
                    send(MES_TURN, previousPos, getPos((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE));
                    
                    // Changing turn
                    waitTurn = true;
                }
            }
        }
        else{
            // Checking exit to menu
            if(data.textButtons[BTN_GAME_MENU].in(mouseX, mouseY)){
                return 1;
            }
        }
    }
    return 0;
};

//
void ClientGameCycle::draw() const{
    // Different draw variants
    if(waitStart){
        // Connecting menu
        // Drawing background
        data.setColor(BLACK);
        SDL_RenderClear(data.renderer);

        // Draw text plates
        data.texts[TXT_CLIENT_ENTER_IP].blit();
        data.texts[TXT_CLIENT_ENTER_PORT].blit();

        // Drawing entering fields
        typeBoxes[0].blit();
        typeBoxes[1].blit();

        // Drawing button for connect and exit
        data.textButtons[BTN_GAME_CONNECT].blit();
        data.textButtons[BTN_GAME_CANCEL].blit();

        // Rendering at screen
        data.render();
    }
    else{
        // Game variant
        // Bliting field
        board.blit();

        // Draw surround letters
        letters.blit();

        // Drawing player state
        data.texts[TXT_GAME_TURN_THIS + waitTurn].blit();

        // Bliting game state, if need
        if(endState > END_TURN){
            // Bliting end background
            endBackplate.blit();

            // Bliting text with end state
            switch (endState)
            {
            case END_WIN:
                data.texts[TXT_END_LOOSE].blit();
                break;
            
            case END_LOOSE:
                data.texts[TXT_END_WIN].blit();
                break;
            
            case END_NOBODY:
                data.texts[TXT_END_NOBODY].blit();
                break;
            }

            // Blitting buttons (without restart option)
            data.textButtons[BTN_GAME_MENU].blit();
        }

        // Bliting all to screen
        data.render();
    }
};
