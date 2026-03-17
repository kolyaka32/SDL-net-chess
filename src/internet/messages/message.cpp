/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "message.hpp"


const char* Message::getData() const {
    return data;
}

size_t Message::getLength() const {
    return size;
}

void Message::write(const char* _str) {
    // Getting it length
    unsigned length = SDL_strlen(_str);

    #if (CHECK_CORRECTION)
    if (size + length > maxSize) {
        logger.important("Can't write data - not enogh size");
        return;
    }
    #endif

    // Copying data
    memcpy(data, _str, length);

    size += length;
}
