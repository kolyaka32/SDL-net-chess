/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "connection.hpp"


class Server : public Connection {
private:
    static Uint16 currentPort;

public:
    void start();
    void stop();
    Uint16 getPort();
    void connectToLastMessage();
};
