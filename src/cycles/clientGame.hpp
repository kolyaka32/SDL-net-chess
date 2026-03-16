/*
 * Copyright (C) 2025-2026, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "internetCycle.hpp"


// Game cycle (for single player (special animation))
class ClientGameCycle : public InternetCycle {
 protected:
    // Additional text
    GUI::StaticText waitText;
    // ! Should add own menu

 protected:
    bool inputMouseDown() override;
    void getInternetPacket(const GetPacket& packet) override;
    void draw() const override;

 public:
    ClientGameCycle(Window& window);
    ~ClientGameCycle();
};
