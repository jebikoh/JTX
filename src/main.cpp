#include <iostream>
#include <jtxlib/math/vec3.hpp>

int main() {
    jtx::Vec3f vec(1.0f, 2.0f, 3.0f);
    std::cout << jtx::toString(vec) << std::endl;
}
