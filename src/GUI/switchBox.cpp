/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"

#if (USE_SDL_FONT) && (PRELOAD_FONTS)


GUI::SwitchBox::SwitchBox(const Window& _window, float _X, float _Y, float _W,
    std::initializer_list<LanguagedText> _texts, unsigned _startOption, float _size, Color _backColor, Color _frontColor)
: Template(_window),
height(_size*1.2f / _window.getHeight()),
backColor(_backColor) {
    // Setting background
    background = {(_X-_W/2)*window.getWidth(), (_Y - height/2)*window.getHeight(),
        _W*window.getWidth(), height*window.getHeight()};

    // Placing select options
    int i=0;
    for (const LanguagedText* text=_texts.begin(); text != _texts.end(); ++text) {
        drawnTexts.emplace_back(_window, (_X-_W/2+0.022), _Y, std::move(*text), _size, _frontColor, GUI::Aligment::Left);
        // Placing text
        drawnTexts[i].move(0.0, height*i);
        i++;
    }
    // Updating start option
    selected = _startOption;

    // Creating arrow
    arrowRect = {background.x+height*0.1f, background.y+height*0.15f, height*0.7f, height*0.7f};
    arrowTexture = window.createTexture(arrowRect.w, arrowRect.h);
    SDL_Vertex vertex[3] = {
        {  // Down point
            {_X+arrowRect.w*0.5f, _Y+arrowRect.h},
            {0.0, 0.0, 0.0, 1.0},  // Black
        },
        {  // Left point
            {_X, _Y},
            {0.0, 0.0, 0.0, 1.0},  // Black
        },
        {  // Right point
            {_X+arrowRect.w, _Y},
            {0.0, 0.0, 0.0, 1.0},  // Black
        },
    };
    window.setDrawColor(_frontColor);
    window.setRenderTarget(arrowTexture);
    window.drawGeometry(vertex, 3);
    window.resetRenderTarget();
}

void GUI::SwitchBox::set(unsigned _value) {
    if (opened) {
        selected = _value;
        opened = false;
        drawnTexts[selected].move(0.0, -height*selected);
        background.h = height * window.getHeight();
    } else {
        // Resetting old option
        drawnTexts[selected].move(0.0, height*selected);

        // Moving new option
        selected = _value;
        drawnTexts[selected].move(0.0, -height*selected);
    }
}

unsigned GUI::SwitchBox::getValue() const {
    return selected;
}

GUI::Code GUI::SwitchBox::click(const Mouse _mouse) {
    if (opened) {
        // Closing
        opened = false;
        // Selecting variant
        if (_mouse.in(background)) {
            // Finding new option
            selected = (_mouse.getY() - background.y) / (height * window.getHeight());
            drawnTexts[selected].move(0.0, -height*selected);
            background.h = height * window.getHeight();
            return Finished;
        }
        // Resetting to previous
        drawnTexts[selected].move(0.0, -height*selected);
        background.h = height * window.getHeight();
        return None;
    } else {
        if (_mouse.in(background)) {
            // Selecting variant
            opened = true;
            background.h = height * drawnTexts.size() * window.getHeight();
            // Resetting selected postion
            drawnTexts[selected].move(0.0, height*selected);
        }
    }
    return None;
}

void GUI::SwitchBox::blit() const {
    // Drawing background
    window.setDrawColor(backColor);
    window.drawRect(background);

    // Draw open or close version depend on state
    if (opened) {
        for (int i=0; i < drawnTexts.size(); ++i) {
            drawnTexts[i].blit();
        }
        window.blit(arrowTexture, 0.0f, arrowRect, nullptr, SDL_FLIP_VERTICAL);
    } else {
        drawnTexts[selected].blit();
        window.blit(arrowTexture, arrowRect);
    }
}

#endif  // (USE_SDL_FONT) && (PRELOAD_FONTS)
