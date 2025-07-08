/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"


class GameConnection : public Connection {
private:
    /* data */

public:
    GameConnection(const Connection& connection);
    ~GameConnection();
};
