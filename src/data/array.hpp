/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once

#include "../define.hpp"
#include "logger.hpp"


// Custom
template <typename T>
class Array {
 private:
    const T* data;
    const unsigned size;

 public:
    Array(const T* data, unsigned size);
    const T& operator[](unsigned index) const;
    const T* getData() const;
    unsigned getSize() const;
};


template <typename T>
Array<T>::Array(const T* _data, unsigned _size)
: data(_data),
size(_size) {}

template <typename T>
const T& Array<T>::operator[](unsigned _index) const {
    // Additional check on correction
    #if CHECK_CORRECTION
    if (_index >= size) {
        logImportant("Wrong address");
    }
    #endif
    return data[_index];
}

template <typename T>
const T* Array<T>::getData() const {
    return data;
}

template <typename T>
unsigned Array<T>::getSize() const {
    return size;
}
