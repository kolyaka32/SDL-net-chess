/*
 * Copyright (C) 2024-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

// Types of cycles, avalible to run
enum class Cycle {
    None,
    Menu,
    Singleplayer,
    Coop,
    ServerLobby,
    ServerGame,
    ClientLobby,
    ClientGame,
};
