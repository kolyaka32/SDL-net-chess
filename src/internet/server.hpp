/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"


class Server : public Connection {
private:
    Uint16 currentPort;

public:
    Server();
    ~Server();
    Uint16 getPort();
    void connectToLastMessage();
};
