/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3_net/SDL_net.h>


// Codes for send/recieve in internet messages
enum class ConnectionCode : Uint8 {
    // System codes
    Null,     // Code of absence of new messages
    Init,     // Code for initialise connection
    Quit,     // Code for break connection (not need aprove)
    Confirm,  // Code for confirm, that importane message was delivered (with number of message)
    ApplyConnection,  // Code of confirmation of continued connection

    // Game codes
    GameRestart,  // Code of restart game with options of new game (field, turn)
    GameTurn,     // Code of normal game turn with it options
};
