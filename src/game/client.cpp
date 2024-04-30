#include "client.hpp"


//
ClientGameCycle::ClientGameCycle()
{

}

//
ClientGameCycle::~ClientGameCycle()
{

}

//
Uint8 ClientGameCycle::getData(){
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