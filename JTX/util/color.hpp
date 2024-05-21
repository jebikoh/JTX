#pragma

namespace JTX::Util {
struct Color {
  float r, g, b;
};
[[maybe_unused]] static const Color WHITE = {255.0f, 255.0f, 255.0f};
[[maybe_unused]] static const Color RED = {255.0f, 0.0f, 0.0f};
[[maybe_unused]] static const Color GREEN = {0.0f, 255.0f, 0.0f};
[[maybe_unused]] static const Color BLUE = {0.0f, 0.0f, 255.0f};
[[maybe_unused]] static const Color BLACK = {0.0f, 0.0f, 0.0f};
} // namespace JTX::Util