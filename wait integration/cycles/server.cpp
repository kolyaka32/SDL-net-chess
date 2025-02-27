/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "server.hpp"

// Server game cycle class
ServerGameCycle::ServerGameCycle() {
    // Setting texture of port box
    portText.updateLocationArgs(1, serverPort);
}

ServerGameCycle::~ServerGameCycle() {
    // Starting playing menu theme if need
    if (!waitStart) {
        data.playMusic(MUS_MENU_THEME);
    }
}

bool ServerGameCycle::getData() {
    switch (recieveData->data[0]) {
    // Code of start connection with other side
    case MES_INIT:
        // Checking, if need start
        if (waitStart) {
            // Setting sender address to place, where was send from
            sendData.address = recieveData->address;

            // Sending init message
            sendNew(MES_INIT);

            // Setting flag of connection to start game
            waitStart = false;

            // Starting playing main theme
            musicOrder.start();

            // Updating times of last sended messages
            lastMessageArrive = SDL_GetTicks64() + MESSAGE_GET_TIMEOUT;
            lastMessageSend = SDL_GetTicks64() + MESSAGE_NULL_TIMEOUT;
        }
        return false;

    // Code of turn of another player
    case MES_TURN:
        // Checking, if current turn of another player
        if (waitTurn && endState <= END_TURN) {
            // Making opponent turn
            endState = board.move(recieveData->data[2] % FIELD_WIDTH, recieveData->data[2] / FIELD_WIDTH,
                recieveData->data[3] % FIELD_WIDTH, recieveData->data[3] / FIELD_WIDTH);

            // Checking, if there was a move
            if (endState) {
                // Allowing current player to move
                waitTurn = false;
            }
        }
        return false;

    // Code of unused/strange message
    default:
        return false;
    }
}

bool ServerGameCycle::getMouseInput() {
    if (exitButton.in(mouseX, mouseY)) {
        // Quit to menu
        return true;
    } else if (settings.click(mouseX, mouseY)) {
        if (waitStart) {
            // Connecting menu variant
            if (cancelButton.in(mouseX, mouseY)) {
                // Closing connection
                return true;
            }
        } else {
            // Game variant
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
                        // Sedning turn
                        sendNew(MES_TURN, {previousPos,
                            (Uint8)getPos((mouseX - LEFT_LINE) / CELL_SIDE, (mouseY - UPPER_LINE) / CELL_SIDE)});

                        // Changing turn
                        waitTurn = true;
                    }
                }
            } else {
                // Game restart
                if (restartButton.in(mouseX, mouseY)) {
                    // Resetting flags
                    endState = END_NONE;
                    waitTurn = false;

                    // Resetting field
                    board.reset();

                    // Sending reset flag
                    sendNew(MES_REST);

                    // Making sound
                    data.playSound(SND_RESET);
                } else if (menuButton.in(mouseX, mouseY)) {
                    // Going to menu
                    return true;
                }
            }
        }
    }
    return false;
}

void ServerGameCycle::draw() const {
    if (waitStart) {
        // Connecting menu
        // Drawing background
        data.setColor(BLACK);
        SDL_RenderClear(data.renderer);

        // Draw text plates
        waitText.blit();
        portText.blit();
        cancelButton.blit();
    } else {
        // Gameplay variant
        // Bliting game field
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
                winText.blit();
                break;

            case END_LOOSE:
                looseText.blit();
                break;

            case END_NOBODY:
                nobodyWinText.blit();
                break;
            }

            // Blitting buttons
            restartButton.blit();
            menuButton.blit();
        }
    }
    // Drawing exit button
    exitButton.blit();

    // Settings menu
    settings.blit();

    data.render();
}
