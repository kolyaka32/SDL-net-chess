/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"


class Client : public Connection {
public:
    Client();
    ~Client();
    void tryConnect(const char* address, Uint16 port);
    void connectToLastMessage();
};
