#pragma

namespace JTX::Util {
/**
 * @brief A struct representing a color in RGB format.
 * Values are in the range [0.0f, 255.0f]
 *
 * TODO: Add support for alpha channel
 * TODO: Switch to [0.0f, 1.0f] range
 */
struct Color {
  float r, g, b;
};
[[maybe_unused]] static const Color WHITE = {255.0f, 255.0f, 255.0f};
[[maybe_unused]] static const Color RED = {255.0f, 0.0f, 0.0f};
[[maybe_unused]] static const Color GREEN = {0.0f, 255.0f, 0.0f};
[[maybe_unused]] static const Color BLUE = {0.0f, 0.0f, 255.0f};
[[maybe_unused]] static const Color BLACK = {0.0f, 0.0f, 0.0f};
} // namespace JTX::Util