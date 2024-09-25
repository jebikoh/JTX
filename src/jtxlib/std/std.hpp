#pragma once
#include "jtxlib.hpp"

#include <algorithm>

JTX_HOSTDEV
template <typename T>
void swap(T &a, T &b) noexcept {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}