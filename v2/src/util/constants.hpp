#pragma once

namespace jtx {
    // TODO: expand as needed
    // Structure from https://github.com/behindthepixels/EDXUtil/
    static struct Zero {
        inline explicit operator int() const { return 0; }
        inline explicit operator float() const { return 0.0f; }
        inline explicit operator double() const { return 0.0; }
    } JTX_ZERO;
}

