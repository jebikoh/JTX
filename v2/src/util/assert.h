/**
 * This file contains assertion macros
 * (There's only one for now)
 */
#pragma once

#include <iostream>

namespace jtx {
#ifndef NDEBUG
#define ASSERT(condition) \
    do {                  \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << std::endl; \
            std::cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << std::endl; \
           std::abort(); \
        } \
    } while (false)
#else
#define ASSERT(condition) ((void) 0)
#endif
}

