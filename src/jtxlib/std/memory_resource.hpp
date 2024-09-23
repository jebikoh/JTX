#pragma once
#include <cstddef>

namespace jtx::pmr {
/**
 * Implementation of the C++17 polymorphic memory resource interface.
 *
 * Main diff from std implementation is some of the return behavior
 *
 * References:
 *  - https://github.com/gcc-mirror/gcc/blob/0121b852c85db91babdb346f277ca6220eb7df86/libstdc%2B%2B-v3/include/bits/memory_resource.h#L61
 *  - https://github.com/mmp/pbrt-v4/blob/39e01e61f8de07b99859df04b271a02a53d9aeb2/src/pbrt/util/pstd.h#L483
 */
class memory_resource {
  static constexpr size_t max_align = alignof(std::max_align_t);

public:
  memory_resource() = default;
  memory_resource(const memory_resource&) = delete;
  virtual ~memory_resource() = default;

  memory_resource &operator=(const memory_resource&) = default;

  [[nodiscard]]
  void *allocate(size_t bytes, size_t alignment = max_align) {
    if (bytes == 0) return nullptr;
    return do_allocate(bytes, alignment);
  }

  void deallocate(void *p, size_t bytes, size_t alignment = max_align) {
    if (p == nullptr) return;
    do_deallocate(p, bytes, alignment);
  }

  void is_equal(const memory_resource &other) const noexcept {
    do_is_equal(other);
  }

private:
  virtual void *do_allocate(size_t bytes, size_t alignment) = 0;
  virtual void  do_deallocate(void *p, size_t bytes, size_t alignment) = 0;
  virtual void  do_is_equal(const memory_resource &other) const noexcept = 0;
};

[[nodiscard]]
inline bool operator ==(const memory_resource &a, const memory_resource &b) noexcept {
  return &a == &b || a.is_equal(b);
}

[[nodiscard]]
inline bool operator !=(const memory_resource &a, const memory_resource &b) noexcept {
  return !(a == b);
}
} // namespace jtx::pmr
