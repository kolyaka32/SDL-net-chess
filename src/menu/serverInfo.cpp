/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "serverInfo.hpp"


ServerInfo::ServerInfo(const Window& _window, int _position, float _height, const ServerData& _data)
: height(_height),
backplate(_window, 0.48, (_position + 1.16f)*_height, 0.9, 0.15, 20, 2),
addressText(_window, 0.1, (_position + 0.9f)*_height, {"Address: %s:%d", "Адрес: %s:%d", "Adresse: %s:%d", "Адрас: %s: %d"},
    Height::Main, WHITE, GUI::Aligment::Left, _data.getAddress().getName(), _data.getAddress().getPort()),
pingText(_window, 0.1, (_position + 0.4f)*_height, {"Ping: %d", "Задержка: %d", "Verzögerung: %d", "Затрымка: %d"},
    Height::Main, WHITE, GUI::Aligment::Left, _data.getPing()) {}

ServerInfo::ServerInfo(ServerInfo&& _object) noexcept
: height(_object.height),
backplate(std::move(_object.backplate)),
addressText(std::move(_object.addressText)),
pingText(std::move(_object.pingText)) {}

void ServerInfo::moveUp() {
    backplate.move(0.0, -height);
    addressText.move(0.0, -height);
    pingText.move(0.0, -height);
}

void ServerInfo::moveDown() {
    backplate.move(0.0, height);
    addressText.move(0.0, height);
    pingText.move(0.0, height);
}

void ServerInfo::blit() const {
    backplate.blit();
    addressText.blit();
    pingText.blit();
}

bool ServerInfo::in(Mouse _mouse) const {
    return backplate.in(_mouse);
}
