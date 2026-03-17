/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../internet/destination.hpp"


// Object contains information of server for list
class ServerData {
 private:
    int ping;
    Destination dest;

 public:
    ServerData(const sockaddr_in* address, int ping);
    // Getters
    int getPing() const;
    const Destination& getAddress() const;
};
