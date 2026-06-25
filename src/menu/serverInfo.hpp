/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../GUI/interface.hpp"
#include "serverData.hpp"


// Info of one server as variant for connection
class ServerInfo {
 private:
    const float height;  // Full height of that unit
    // Graphical elements
    GUI::RoundedBackplate backplate;
    GUI::StaticText addressText;
    GUI::StaticText pingText;

 public:
    ServerInfo(const Window& window, float height, float Y, const ServerData& data);
    ServerInfo(ServerInfo&& info) noexcept;
    void moveUp();
    void moveDown();
    void blit() const;
    bool in(Mouse mouse) const;
};
