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
