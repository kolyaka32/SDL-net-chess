/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "client.hpp"

ClientGameCycle::ClientGameCycle() {
    // Resetting values
    lastTypeBoxUpdate = 0;  // Setting to 0 to update as early as can
}

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
        selecting = false;
    }
}

bool ClientGameCycle::getData() {
    switch (recieveData->data[0]) {
    // Code of initialasing connection
    case MES_INIT:
        // Checking, if get first init message
        if (waitStart) {
            // Starting playing main theme
            musicOrder.start();

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

bool ClientGameCycle::getAnotherInput(const SDL_Event& event) {
    // Checking on game variant
    if (waitStart) {
        // Entering data variant
        switch (event.type) {
        case SDL_TEXTINPUT:
            // Typing text on which object is selected
            if (selectedBox) {
                typeBoxes[selectedBox - 1].writeString(event.text.text);
            }
            return false;

        // Checking, if mouse was unclicked (for end selection)
        case SDL_MOUSEBUTTONUP:
            //
            selecting = false;
            return false;

        // Check, if key was unclicked
        case SDL_KEYUP:
            typeBoxes[selectedBox - 1].resetPress(event.key.keysym.sym);
            return false;
        }
    } else {
        settings.getAnotherInput(event);
    }
    return false;
}

// Example for getting keys input
bool ClientGameCycle::getKeysInput(const SDL_Keysym& key) {
    // Check game variant
    if (waitStart) {
        // Entering mode
        switch (key.sym) {
        case SDLK_ESCAPE:
            removeSelection();
            return false;

        case SDLK_RETURN:
        case SDLK_RETURN2:
        case SDLK_KP_ENTER:
            removeSelection();
            // Trying connect at address
            tryConnect(typeBoxes[0].getString(), typeBoxes[1].getString());
            return false;

        default:
            // Typing in selected box
            selecting = false;
            if (selectedBox) {
                typeBoxes[selectedBox - 1].press(key.sym);
            }
            return false;
        }
    } else {
        switch (key.sym) {
        case SDLK_ESCAPE:
            // Clearing selection by escape
            if (board.isFigureSelected()) {
                board.resetSelection();
            // Or go to setting menu
            } else {
                settings.activate();
            }
            return false;

        case SDLK_q:
            // Quiting to menu
            return true;
        }
    }
    return false;
}

void ClientGameCycle::update() {
    if (waitStart) {
        // Check, if selecting text
        if (selecting) {
            SDL_GetMouseState(&mouseX, nullptr);
            typeBoxes[selectedBox - 1].updateSelection(mouseX);
        } else if (selectedBox && (SDL_GetTicks64() > lastTypeBoxUpdate)) {
            // Blinking caret in type box
            typeBoxes[selectedBox - 1].updateCaret();
            lastTypeBoxUpdate = SDL_GetTicks64() + 500;
        }
    } else {
        musicOrder.update();
        settings.update();
    }
}

bool ClientGameCycle::getMouseInput() {
    if (exitButton.in(mouseX, mouseY)) {
        return true;
    } else if (settings.click(mouseX, mouseY)) {
        // Different draw variants
        if (waitStart) {
            // Connecting menu
            // Connect to server button
            if (connectButton.in(mouseX, mouseY)) {
                removeSelection();
                // Trying connect at address
                tryConnect(typeBoxes[0].getString(), typeBoxes[1].getString());
                return false;
            } else if (cancelButton.in(mouseX, mouseY)) {
                // Returning to menu
                removeSelection();
                return true;
            }
            // Selecting need box
            for (Uint8 i=0; i < 2; ++i) {
                // Checking, if click on that box
                if (typeBoxes[i].in(mouseX, mouseY)) {
                    // Removing previous selection
                    removeSelection();
                    // New selection
                    selectedBox = i+1;
                    typeBoxes[i].select(mouseX);
                    selecting = true;
                    lastTypeBoxUpdate = SDL_GetTicks64() + 700;
                    return false;
                }
            }
            // If press on somewhere else on field - resetting selection
            removeSelection();
            return false;
        } else {
            // Game variant
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
                // Waiting start menu
                if (menuButton.in(mouseX, mouseY)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void ClientGameCycle::draw() const {
    // Different draw variants
    if (waitStart) {
        // Connecting menu
        // Drawing background
        data.setColor(BLACK);
        SDL_RenderClear(data.renderer);

        // Draw text plates
        enterIPText.blit();
        enterPortText.blit();

        // Drawing entering fields
        typeBoxes[0].blit();
        typeBoxes[1].blit();

        // Drawing button for connect and exit
        connectButton.blit();
        cancelButton.blit();
    } else {
        // Game variant
        // Bliting field
        board.blit();

        // Draw surround letters
        letters.blit();

        // Drawing player state
        playersTurnsTexts[waitTurn + 2].blit();

        // Bliting game state, if need
        if (endState > END_TURN) {
            // Bliting end background
            endBackplate.blit();

            // Bliting text with end state
            switch (endState) {
            case END_WIN:
                looseText.blit();
                break;

            case END_LOOSE:
                winText.blit();
                break;

            case END_NOBODY:
                nobodyWinText.blit();
                break;
            }

            // Blitting buttons (without restart option)
            menuButton.blit();
        }
    }
    exitButton.blit();
    settings.blit();

    // Bliting all to screen
    data.render();
}
