/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Types of cycles, avalible to run
enum class Cycle {
    None,
    Menu,
    Singleplayer,
    LocalCOOP,
    ServerLobby,
    ServerGame,
    ClientLobby,
    ClientGame,
};
