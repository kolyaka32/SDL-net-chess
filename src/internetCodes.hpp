/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include <SDL3/SDL_stdinc.h>
#include "define.hpp"


// Codes for send/recieve in internet messages
enum class ConnectionCode : Uint8 {
    // System codes
    Null,     // Code of absence of new messages (need for apply connection)
    Init,     // Code for initialise connection
    Quit,     // Code for break connection (not need aprove)
    Confirm,  // Code for confirm, that importane message was delivered (with number of message)
    ApplyConnection,  // Code of confirmation of continued connection
    // Broadcast
    Search,   // Code for search of servers in subnet
    Server,   // Code for server to say, where it is

    // Game codes
    // Global
    GameTurn,     // Code of normal game turn with it options
    // Server-side
    GameNew,      // Code of sending new field
};
