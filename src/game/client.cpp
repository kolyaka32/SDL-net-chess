/*
 * Copyright (C) 2024, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "client.hpp"

//
ClientGameCycle::ClientGameCycle() {
    // Resetting values
    lastTypeBoxUpdate = 0;  // Setting to 0 to update as early as can
}

//
ClientGameCycle::~ClientGameCycle() {
    // Additional stopping text input on case, when was closed at inputting
    removeSelection();

    // Starting playing menu theme if need
    if (!waitStart) {
        data.playMusic(MUS_MENU_THEME);
    }
}

// Macros for removing select from typeBox
void ClientGameCycle::removeSelection() {
    if (selectedBox) {
        typeBoxes[selectedBox - 1].removeSelect();
        selectedBox = 0;
    }
}

//
bool ClientGameCycle::getData() {
    //
    switch (recieveData->data[0]) {
    // Code of initialasing connection
    case MES_INIT:
        // Checking, if get first init message
        if (waitStart) {
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
        if (waitTurn && endState <= END_TURN) {
            // Making opponent turn
            endState = board.move(recieveData->data[2] % FIELD_WIDTH, recieveData->data[2] / FIELD_WIDTH,
                recieveData->data[3] % FIELD_WIDTH, recieveData->data[3] / FIELD_WIDTH);

            // Allowing current player to move
            if (endState) {
                waitTurn = false;
            }
        }
        return 0;

    // Strange/unused code
    default:
        return false;
    }
}

// Getting text input
bool ClientGameCycle::getAnotherInput(SDL_Event& event) {
    // Checking on game variant
    if (waitStart) {
        // Entering data variant
        switch (event.type) {
        case SDL_TEXTINPUT:
            // Typing text on which object is selected
            if (selectedBox) {
                typeBoxes[selectedBox - 1].writeString(event.text.text, false);
            }
            return false;
        }
    }
    return false;
}

// Example for getting keys input
bool ClientGameCycle::getKeysInput(SDL_Keysym& key) {
    // Check game variant
    if (waitStart) {
        // Entering mode
        switch (key.sym) {
        case SDLK_ESCAPE:
            // Removing selection from
            removeSelection();
            return false;

        case SDLK_RETURN:
        case SDLK_RETURN2:
        case SDLK_KP_ENTER:
            removeSelection();
            // Trying connect at address
            tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer);
            return false;

        default:
            // Typing in selected box
            if (selectedBox) {
                typeBoxes[selectedBox - 1].press(key.sym);
            }
            return false;
        }
    } else {
        switch (key.sym) {
        case SDLK_ESCAPE:
            // Clearing selection by escape
            board.resetSelection();
            return false;

        case SDLK_q:
            // Quiting to menu
            return true;

        default:
            // None-return
            return false;
        }
    }
}

// Updating text caret
void ClientGameCycle::update() {
    // Check, if entering text and need to blink caret in type box
    if (waitStart && selectedBox && (SDL_GetTicks64() > lastTypeBoxUpdate)) {
        // Updating type box for show place to type
        typeBoxes[selectedBox - 1].updateCaret();
        lastTypeBoxUpdate = SDL_GetTicks64() + 500;
    }
}


//
bool ClientGameCycle::getMouseInput() {
    // Different draw variants
    if (waitStart) {
        // Connecting menu
        // Connect to server button
        if (data.textButtons[BTN_GAME_CONNECT].in(mouseX, mouseY)) {
            removeSelection();
            // Trying connect at address
            tryConnect(typeBoxes[0].buffer, typeBoxes[1].buffer);
            return 0;
        } else if (data.textButtons[BTN_GAME_CANCEL].in(mouseX, mouseY)) {
            // Returning to menu
            removeSelection();
            return 1;
        }
        // Selecting need box
        for (Uint8 i=0; i < 2; ++i) {
            // Checking, if click on that box
            if (typeBoxes[i].in(mouseX, mouseY)) {
                // Checking, if box not selected
                if (selectedBox != i+1) {
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
    } else {
        // Game variantwaitTurn = true;
        // Pause button
        /*if (settingButton.in(mouseX, mouseY)) {
            return 1;
        }*/

        // Clicking on field if possible
        if (endState <= END_TURN) {
            // Checking, if current turn this player
            if (!waitTurn) {
                // Getting previous click
                position previousPos = board.getPreviousTurn();

                // Normal clicking on field
                endState = board.click((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE);

                // Checking, if need send move
                if (endState) {
                    // Sending turn
                    sendNew(MES_TURN, {(Uint8)previousPos,
                        (Uint8)getPos((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE)});

                    // Changing turn
                    waitTurn = true;
                }
            }
        } else {
            // Checking exit to menu
            if (data.textButtons[BTN_GAME_MENU].in(mouseX, mouseY)) {
                return 1;
            }
        }
    }
    return 0;
}

//
void ClientGameCycle::draw() const {
    // Different draw variants
    if (waitStart) {
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
    } else {
        // Game variant
        // Bliting field
        board.blit();

        // Draw surround letters
        letters.blit();

        // Drawing player state
        data.texts[TXT_GAME_TURN_THIS + waitTurn].blit();

        // Bliting game state, if need
        if (endState > END_TURN) {
            // Bliting end background
            endBackplate.blit();

            // Bliting text with end state
            switch (endState) {
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
}
