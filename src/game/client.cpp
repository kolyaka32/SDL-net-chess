#include "client.hpp"

//
ClientGameCycle::ClientGameCycle()
{
    // Starting text inputing
    SDL_StartTextInput();

    // Allowing internet to start
    gettingMutex.unlock();
}

//
ClientGameCycle::~ClientGameCycle()
{
    // Additional stopping text input on case, when was closed at inputting
    SDL_StopTextInput();
}

// Macros for removing select from typeBox
void ClientGameCycle::removeSelection(){
    if(selectedBox){
        typeBoxes[selectedBox - 1].removeSelect();\
        selectedBox = 0; 
    }
}

//
Uint8 ClientGameCycle::getData(){
    //
    switch (recieveData->data[0])
    {
    // Code of initialasing connection
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
    while(true){
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

                case SDL_MOUSEBUTTONUP:
                    //LMBclick = false;
                    selectedBox = 0;
                    break;

                }
                // Checking, if need to blink in type box
                if(selectedBox && (SDL_GetTicks64() > lastTypeBoxUpdate)){
                    // Updating type box for show place to type
                    typeBoxes[selectedBox-1].updateCaret();
                    lastTypeBoxUpdate = SDL_GetTicks64() + 500;
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
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        return;
                    };
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
            // Waiting next cycle
            data.waitDraw();
        }
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
            return tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer);
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
                    typeBoxes[0].select();
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
        // Game variant
        // Pause button
        /*if(settingButton.in(mouseX, mouseY)){
            return 1;
        }*/

        // Clicking on field if possible
        if(endState <= END_NONE){
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

            // Blitting buttons (without restart option)
            data.textButtons[BTN_GAME_MENU].blit();
        }

        // Bliting all to screen
        data.render();
    }
};

//
void ClientGameCycle::initConnection(){
    // Stopping inputing text
    SDL_StopTextInput();

    // Setting flag of connection to start game
    waitStart = false;
};


/*

// Cycle for user enter, where connect to
static inline Uint8 enteringCycle(){
    
    bool waiting = true;       // Flag of internal cycle
    Uint8 inBox = 0;           // Selected window to interact with (or 0 for none)
    timer lastTypeBoxUpdate;  // Timer for change symbol of caret

    while(waiting){
        while( SDL_PollEvent(&event) != 0 ){
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;  // Exit from program
                runGame = false;
                return 1;

            case SDL_TEXTINPUT:
                // Typing text on which object is selected
                if(inBox){
                    typeBoxes[inBox - 1].writeString(event.text.text, false);
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    removeTypeBox();
                    break;
                
                case SDLK_RETURN:
                case SDLK_RETURN2:
                case SDLK_KP_ENTER:
                    removeTypeBox();
                    tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer, &waiting);
                    break;
                
                default:
                    if(inBox){
                        typeBoxes[inBox - 1].press(event.key.keysym.sym);
                    }
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position
                // Checking pressing on connect button
                if(connectButton.in(MouseX, MouseY)){
                    removeTypeBox();
                    tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer, &waiting);
                }
                else if(menuButton.in(MouseX, MouseY)){
                    // Returning to menu
                    removeTypeBox();
                    runGame = false;
                    return 2;
                }
                else if(typeBoxes[0].in(MouseX, MouseY)){
                    if(inBox != 1){
                        inBox = 1;
                        typeBoxes[0].select();
                        lastTypeBoxUpdate = SDL_GetTicks64() + 700;
                    }
                }
                else if(typeBoxes[1].in(MouseX, MouseY)){
                    if(inBox != 2){
                        inBox = 2;
                        typeBoxes[1].select();
                        lastTypeBoxUpdate = SDL_GetTicks64() + 700;
                    }
                }
                else{
                    removeTypeBox();
                }
                break;
            }
        }

        // Checking, if need to blink in type box
        if(inBox && (SDL_GetTicks64() > lastTypeBoxUpdate)){
            // Updating type box for show place to type
            typeBoxes[inBox-1].updateCaret();
            lastTypeBoxUpdate = SDL_GetTicks64() + 500;
        }

        // Drawing
        SDL_RenderClear(renderer);

        texts[TXT_CLIENT_IP].blit();
        typeBoxes[0].blit();
        texts[TXT_CLIENT_PORT].blit();
        typeBoxes[1].blit();

        connectButton.blit();
        menuButton.blit();

        // Blitting textures on screen
        SDL_RenderPresent(renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);
    }
    return 0;  // Exiting without any errors
}

// Menu for waiting to go to menu/game restart (from server)
static inline void stopMenu(){

}

// Main game cycle
static inline void gameCycle(){
    // Preparing for game
    SDL_Event event;
    field.reset();
    waitTurn = true;
    start = true;

    // Resetting messgae timeout
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
                break;

            case SDL_MOUSEBUTTONDOWN:
                int MouseX, MouseY;
                SDL_GetMouseState(&MouseX, &MouseY);  // Getting mouse position

                // Finding place of clicking
                if(!(start || waitTurn) && field.clickMulti(MouseX / (CELL_SIDE + SEPARATOR), MouseY / (CELL_SIDE + SEPARATOR))){
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
            switch (recieveData->data[0])
            {
            case MES_START:
                // Getting start
                start = false;

                queue = 1 - recieveData->data[1];  // Inverting order of players
                player = queue;
                waitTurn = queue;
                break;

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

            case MES_REST:
                // Code of restart game
                field.reset();
                player = 0;
                start = true;
                waitTurn = true;
                break;

            case MES_APPL:
                // Last send message arrive normaly
                waitApply = false;
                break;

            case MES_SKIP:
                // Skipping round
                gameState = END_SKIP;
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
        };

        // Checking end of game
        if(gameState){
            // His own waiting menu
            stopMenu();
        }

        // Drawing
        SDL_RenderClear(process.app.renderer);
        
        field.blit();

        // Showing game chose
        if(start){
            // Showing text for Activation
            texts[TXT_CLIENT_WAIT].blit();
        }
        else if(waitTurn)
            texts[TXT_INTERNET_WAIT].blit();
        else
            texts[TXT_INTERNET_TURN].blit();

        // Blitting textures on screen
        SDL_RenderPresent(process.app.renderer); 

        // Delaying time to decrease CPU loading
        SDL_Delay(1000 / drawFPS);  
    }
    // Sending message of server disabling
    send(MES_STOP);
}

// Main game client cycle
void multiMainClient(){
    // Setting main game cycle to run after "entering cycle"
    runGame = true;

    // Getting data from user, where connect to
    if(enteringCycle()){
        // Exiting program to menu
        SDLNet_UDP_Close(socket);
        SDLNet_FreePacket(sendData);
        SDLNet_FreePacket(recieveData);
        return;
    }
 
    // Getting test data from server to control correction
    if(recieveData->data[0] || recieveData->data[1] != fieldWidth || recieveData->data[2] != winWidth){
        // Something wrong with test pachage
        
        // Creating button for asking to restart
        const SDL_MessageBoxColorScheme colorScheme = {{
            { 255,   0,   0 },
            {   0, 255,   0 },
            { 255, 255,   0 },
            {   0,   0, 255 },
            { 255,   0, 255 }
        }};
        int buttonid = 0;  // Field for answer
        
        if(language == LNG_ENGLISH){
            const SDL_MessageBoxButtonData buttons[] = {
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "cancel" },
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "reload" },
            };
            const SDL_MessageBoxData messageBox = {
                SDL_MESSAGEBOX_WARNING,
                app.window,
                "Data doesn't match",
                "Your load configuration donesn't match with server, do you want restart?",
                SDL_arraysize(buttons),
                buttons,
                &colorScheme
            };
            SDL_ShowMessageBox(&messageBox, &buttonid);
        }
        else{
            const SDL_MessageBoxButtonData buttons[] = {
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "отмена" },
                { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "перезагрузка" },
            };
            const SDL_MessageBoxData messageBox = {
                SDL_MESSAGEBOX_WARNING,
                app.window,
                "Данные не сходятся",
                "Ваши загруженные данные не сходятся с сервером, хотите перезагрузится?",
                SDL_arraysize(buttons),
                buttons,
                &colorScheme
            };
            SDL_ShowMessageBox(&messageBox, &buttonid);
        }
        // Checking answer
        if (buttonid == 2) {
            // If user want to reload
            restart = true;
            fieldWidth = recieveData->data[1];
            winWidth = recieveData->data[2];
            running = false;
        }
    }

    // Entering main game cycle, where he play
    gameCycle();
}*/