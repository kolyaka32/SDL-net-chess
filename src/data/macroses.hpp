/*
 * Copyright (C) 2024-2026, Kazankov Nikolay
 * <nik.kazankov.05@mail.ru>
 */

#pragma once


template <typename T>
constexpr T max(const T a, const T b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

template <typename T>
constexpr T min(const T a, const T b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

template <typename T>
constexpr void setMax(T& setting, const T border) {
    if (setting > border) {
        setting = border;
    }
}

template <typename T>
constexpr void setMin(T& setting, const T border) {
    if (setting < border) {
        setting = border;
    }
}

template <typename T>
constexpr T sqr(const T value) {
    return value*value;
}

template <typename T, typename ...Args>
constexpr T sum(const T& value, const Args& ...args) {
    return value + sum(args...);
}
