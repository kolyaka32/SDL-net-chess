/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saveInfo.hpp"


SaveInfo::SaveInfo(const Window& _window, int _position, float _height, const FieldSave& _field)
: height(_height),
TextureTemplate(_window, {0.06f * _window.getWidth(), (_position + 0.7f) * _height * _window.getHeight(),
    height * 0.9f * _window.getHeight(), height * 0.9f * _window.getHeight()},
    _window.createTexture(GAME_WIDTH, GAME_HEIGHT)),
backplate(_window, 0.48, (_position + 1.15f)*_height, 0.9, _height, 15, 2),
//saveNameText(_window, 0.75, (position + 0.8f)*_height, {field.getSaveName()}),
lastModifiedText(_window, 0.25, (_position + 1.1f)*_height, {_field.getSaveTime()}, 1, Height::Main, WHITE, GUI::Aligment::Left) {
    // Creating texture
    _window.setRenderTarget(texture);
    // Render full field at it
    _field.blit(_window);
    _window.resetRenderTarget();
}

SaveInfo::SaveInfo(SaveInfo&& _object) noexcept
: height(_object.height),
TextureTemplate(std::move(_object)),
backplate(std::move(_object.backplate)),
//saveNameText(std::move(_object.saveNameText)),
lastModifiedText(std::move(_object.lastModifiedText)) {}

SaveInfo::~SaveInfo() noexcept {
    if (texture) {
        window.destroy(texture);
    }
}

void SaveInfo::moveUp() {
    backplate.move(0, -height);
    lastModifiedText.move(0, -height);
    rect.y -= height*window.getHeight();
}

void SaveInfo::moveDown() {
    backplate.move(0, height);
    lastModifiedText.move(0, height);
    rect.y += height*window.getHeight();
}

bool SaveInfo::in(Mouse _mouse) const {
    return backplate.in(_mouse);
}

void SaveInfo::blit() const {
    backplate.blit();
    window.blit(texture, rect);
    //saveNameText.blit();
    lastModifiedText.blit();
}
