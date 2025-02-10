/*
 * Copyright (C) 2025, Kazankov Nikolay 
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

using namespace GUI;


// Button class
TextButton::TextButton(const char* _text, textHeight _size, float _X, float _Y,
    SDL_Color _color, ALIGNMENT_types _alignment)
: topText(_text, _size, _X, _Y, _color, _alignment), Backplate(_size*0.75, 3) {
    updateLocation();

    // Adding item to global updation list
    //data.updateList.add(this);
}

//
void TextButton::blit(Window& _target) const {
    _target.blit(texture, &rect);
    topText.blit(_target);
}

// Update current text plate
void TextButton::updateLocation() {
    // Updating backplate
    updatePlate({topText.rect.x-10, topText.rect.y-1, topText.rect.w+20, topText.rect.h+4});
}
