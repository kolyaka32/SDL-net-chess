/*
 * Copyright (C) 2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#include "indexesArray.hpp"
#include "../../data/logger.hpp"


template <unsigned length>
IndexesArray<length>::IndexesArray()
: array() {
    lastPosition = 0;
}

/*template <unsigned length>
IndexesArray<length>::IndexesArray(const IndexesArray& _object)
: array(_object.array),
lastPosition(_object.lastPosition) {}

template <unsigned length>
IndexesArray<length>& IndexesArray<length>::operator=(const IndexesArray& _object) {
    array = _object.array;
    lastPosition = _object.lastPosition;
    return *this;
}

template <unsigned length>
IndexesArray<length>::IndexesArray(IndexesArray&& _object) noexcept
: array(std::move(_object.array)),
lastPosition(_object.lastPosition) {}*/

template <unsigned length>
bool IndexesArray<length>::isUnique(Uint8 _index) {
    // Check, if index in array
    for (int i=0; i < length; ++i) {
        if (array[i] == _index) {
            logAdditional("Index: %u was already get", _index);
            return false;
        }
    }
    // Adding to list
    add(_index);
    return true;
}

template <unsigned length>
void IndexesArray<length>::add(Uint8 _index) {
    // Adding new index to array, replacing older
    array[lastPosition] = _index;
    // Changing caret postion to next
    lastPosition = (lastPosition + 1) % length;
}
