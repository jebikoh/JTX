/**
 * This file contains assertion macros
 * (There's only one for now)
 */
#pragma once

#include <iostream>

#ifdef JTX_NDEBUG
#define ASSERT(condition) ((void) 0)
#elif defined(JTX_TEST)
#define ASSERT(condition) \
    do {                  \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << std::endl; \
            std::cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << std::endl; \
        } \
    } while (false)
#else
#define ASSERT(condition) \
    do {                  \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << #condition << std::endl; \
            std::cerr << "File: " << __FILE__ << ", Line: " << __LINE__ << std::endl; \
           std::abort(); \
        } \
    } while (false)
#endif