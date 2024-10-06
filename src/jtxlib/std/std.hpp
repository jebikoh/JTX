#pragma once
#include "jtxlib.hpp"

#include <algorithm>

namespace jtx {
JTX_HOSTDEV
template <typename T>
void swap(T &a, T &b) noexcept {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

template <typename T, int N>
class array {
public:
    using value_type = T;
    using iterator = value_type *;
    using const_iterator = const value_type *;
    using size_t = std::size_t;

    array() = default;

    JTX_HOSTDEV
    array(std::initializer_list<T> v) {
        size_t i = 0;
        for (const T &val: v) _data[i++] = val;
    }

    JTX_HOSTDEV
    void fill (const T &v) {
        for (int i = 0; i < N; ++i) _data[i] = v;
    }

    JTX_HOSTDEV
    bool operator==(const array<T, N> &a) const {
        for (int i = 0; i < N; ++i) {
            if (_data[i] != a[i]) return false;
        }
        return true;
    }

    JTX_HOSTDEV
    bool operator!=(const array<T, N> &a) const { return !(*this == a); }

    JTX_HOSTDEV
    iterator begin() { return _data; }

    JTX_HOSTDEV
    iterator end() { return _data + N; }

    JTX_HOSTDEV
    const_iterator begin() const { return _data; }

    JTX_HOSTDEV
    const_iterator end() const { return _data + N; }

    JTX_HOSTDEV
    size_t size() const { return N; }

    JTX_HOSTDEV
    T &operator[](size_t i) { return _data[i]; }

    JTX_HOSTDEV
    const T &operator[](size_t i) const { return _data[i]; }

    JTX_HOSTDEV
    T *data() { return data; }

    JTX_HOSTDEV
    const T *data() const { return data; }

private:
    T _data[N] = {};
};
}

