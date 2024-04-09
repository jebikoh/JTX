#pragma once

#include "JTX/Util/Vec3.h"
#include "JTX/Util/Mat4.h"
#include <cmath>

namespace JTX::Util {
    inline float degToRad(float deg) { return deg * (M_PI / 180.0f); }
}