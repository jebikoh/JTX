#pragma once

namespace jtx {
    // TODO: expand as needed
    // Structure from https://github.com/behindthepixels/EDXUtil/
    static struct Zero {
        inline explicit operator int() const { return 0; }

        inline explicit operator float() const { return 0.0f; }

        inline explicit operator double() const { return 0.0; }

        template<typename T>
        inline bool operator==(const T &other) const {
            return static_cast<T>(*this) == other;
        }

        template<typename T>
        inline bool operator!=(const T &other) const {
            return static_cast<T>(*this) != other;
        }
    } JTX_ZERO;
}

