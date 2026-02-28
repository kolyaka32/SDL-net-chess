/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "baseGUI.hpp"


template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::ScrollBox(const Window& _window, float _posX, float _posY, float _width, float _height,
    int _maxItems, const LanguagedText&& _emptyItemsText)
: Template(_window),
#if (USE_SDL_FONT) && (PRELOAD_FONTS)
emptySavesText(_window, _posX, _posY - _height/4, std::move(_emptyItemsText), 1),
#endif
maxItems(_maxItems),
sliderBackRect({(_posX+_width/2-0.04f)*_window.getWidth(), (_posY - _height/2)*_window.getHeight(),
    0.03f * _window.getWidth(), _height*_window.getHeight()}) {
    startField = 0;
    endField = 0;
    // Side slider
    sliderRect.x = sliderBackRect.x+0.005f*_window.getWidth();
    sliderRect.w = 0.02f*_window.getWidth();
    // Basic full version
    sliderRect.h = sliderBackRect.h;
    sliderRect.y = sliderBackRect.y;
}

template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::ScrollBox(const Window& _window, float _posX, float _posY, float _width, float _height,
    int _maxItems, std::vector<SourceItem> _startItems, const LanguagedText&& _emptyItemsText)
: ScrollBox(_window, _posX, _posY, _width, _height, _maxItems, std::move(_emptyItemsText)) {
    // Creating options to start
    items.reserve(_startItems.size());
    for (int i=0; i < _startItems.size(); ++i) {
        items.emplace_back(_window, _startItems.size()-i-1, _startItems[i]);
    }
    endField = items.size();
    // If has more items, than can show
    if (items.size() > maxItems) {
        startField = endField-maxItems;
        sliderRect.h = float(maxItems) / items.size() * sliderBackRect.h;
        sliderRect.y = (1 - float(endField) / items.size()) * sliderBackRect.h + sliderBackRect.y;
    }
}

template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::ScrollBox(ScrollBox&& _object) noexcept 
: Template(_object.window),
startField(_object.startField),
endField(_object.endField),
maxItems(_object.maxItems),
#if (USE_SDL_FONT) && (PRELOAD_FONTS)
emptySavesText(std::move(_object.emptySavesText)),
#endif
sliderRect(_object.sliderRect),
sliderBackRect(_object.sliderBackRect),
holding(_object.holding),
holdPosition(_object.holdPosition) {}

template <class Item, class SourceItem>
GUI::ScrollBox<Item, SourceItem>::~ScrollBox() noexcept {
    items.clear();
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::addItem(const SourceItem& _sourceItem) {
    // Check, if add, when has place
    if (endField < maxItems) {
        // Moving all infos
        for (int i=0; i < items.size(); ++i) {
            items[i].moveDown();
        }
        items.emplace_back(window, 0, _sourceItem);
        endField++;
        // Not changing slider
        return;
    }
    // Check, if need to save current position in list
    if (endField == items.size()) {
        // Moving all down
        for (int i=0; i < items.size(); ++i) {
            items[i].moveDown();
        }
        items.emplace_back(window, 0, _sourceItem);
        endField++;
        startField++;
        // Changing slider
        sliderRect.h = float(maxItems) / items.size() * sliderBackRect.h;
        sliderRect.y = (1 - float(endField) / items.size()) * sliderBackRect.h + sliderBackRect.y;
        return;
    }
    // Placing and not showing
    items.emplace_back(window, startField - endField, _sourceItem);
    // Changing slider
    sliderRect.h = float(maxItems) / items.size() * sliderBackRect.h;
    sliderRect.y = (1 - float(endField) / items.size()) * sliderBackRect.h + sliderBackRect.y;
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::clear() {
    items.clear();
    startField = 0;
    endField = 0;
    sliderRect.h = sliderBackRect.h;
    sliderRect.y = sliderBackRect.y;
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::moveUp() {
    startField--;
    endField--;
    for (int i=0; i < items.size(); ++i) {
        items[i].moveUp();
    }
    sliderRect.y += sliderRect.h / maxItems;
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::moveDown() {
    startField++;
    endField++;
    for (int i=0; i < items.size(); ++i) {
        items[i].moveDown();
    }
    sliderRect.y -= sliderRect.h / maxItems;
}

template <class Item, class SourceItem>
int GUI::ScrollBox<Item, SourceItem>::click(const Mouse _mouse) {
    if (_mouse.in(sliderBackRect)) {
        if (_mouse.in(sliderRect)) {
            holding = true;
            holdPosition = _mouse.getY();
        }
        return 0;
    }
    for (int i=startField; i < endField; ++i) {
        if (items[i].in(_mouse)) {
            return i+1;
        }
    }
    return 0;
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::unclick() {
    holding = false;
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::update(const Mouse _mouse) {
    if (holding) {
        int delta = (_mouse.getY() - holdPosition) * maxItems / sliderRect.h;
        if (delta) {
            if (delta > 0) {
                if (startField > 0) {
                    moveUp();
                    holdPosition += sliderRect.h / maxItems;
                }
            } else {
                if (endField < items.size()) {
                    moveDown();
                    holdPosition -= sliderRect.h / maxItems;
                }
            }
        }
    }
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::scroll(const Mouse _mouse, float _wheelY) {
    // Check, if scroll in this menu
    if (!holding) {
        if (_wheelY > 0) {
            for (;_wheelY > 0; --_wheelY) {
                // Check, if can scroll up
                if (endField < items.size()) {
                    moveDown();
                } else {
                    return;
                }
            }
        } else {
            for (;_wheelY < 0; ++_wheelY) {
                // Check, if can scroll down
                if (startField > 0) {
                    moveUp();
                } else {
                    return;
                }
            }
        }
    }
}

template <class Item, class SourceItem>
void GUI::ScrollBox<Item, SourceItem>::blit() const {
    // Check, if has fields
    if (endField) {
        for (int i=startField; i < endField; ++i) {
            items[i].blit();
        }
    } else {
        #if (USE_SDL_FONT) && (PRELOAD_FONTS)
        emptySavesText.blit();
        #endif
    }
    // Slider bar
    window.setDrawColor(BLACK);
    window.drawRect(sliderBackRect);
    window.setDrawColor(GREY);
    window.drawRect(sliderRect);
}
