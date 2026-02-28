/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "saveInfo.hpp"


SaveInfo::SaveInfo(const Window& _window, int _position, const Field& _field)
: TextureTemplate(_window, {0.06f * _window.getWidth(), (_position*0.2f + 0.14f) * _window.getHeight(),
    0.18f * _window.getWidth(), 0.18f * _window.getHeight()},
    _window.createTexture(_field.getWindowWidth(), _field.getWindowWidth())),
backplate(_window, 0.48, _position*0.2f+0.23f, 0.9, 0.2, 15, 2),
//saveNameText(_window, 0.75, position*0.2f+0.16f, {field.getSaveName()}),
lastModifiedText(_window, 0.25, _position*0.2f+0.23f, {_field.getSaveTime()}, 1, Height::Main, WHITE, GUI::Aligment::Left) {
    // Creating texture
    _window.setRenderTarget(texture);
    // Render full field at it
    _field.blitIcon(_window);
    _window.resetRenderTarget();
}

SaveInfo::SaveInfo(SaveInfo&& _object) noexcept
: TextureTemplate(std::move(_object)),
backplate(std::move(_object.backplate)),
//saveNameText(_object.saveNameText),
lastModifiedText(std::move(_object.lastModifiedText)) {}

SaveInfo::~SaveInfo() noexcept {
    if (texture) {
        window.destroy(texture);
    }
}

void SaveInfo::moveUp() {
    backplate.move(0, -0.2);
    lastModifiedText.move(0, -0.2);
    rect.y -= 0.2*window.getHeight();
}

void SaveInfo::moveDown() {
    backplate.move(0, 0.2);
    lastModifiedText.move(0, 0.2);
    rect.y += 0.2*window.getHeight();
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
