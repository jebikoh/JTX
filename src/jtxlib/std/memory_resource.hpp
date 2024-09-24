#pragma once
#include <cstddef>
#include <utility>

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
inline bool operator==(const memory_resource &a, const memory_resource &b) noexcept {
  return &a == &b || a.is_equal(b);
}

[[nodiscard]]
inline bool operator!=(const memory_resource &a, const memory_resource &b) noexcept {
  return !(a == b);
}

/**
 * Implementation of the C++17 polymorphic allocator interface.
 *
 * References:
 *  -
 * https://github.com/gcc-mirror/gcc/blob/0121b852c85db91babdb346f277ca6220eb7df86/libstdc%2B%2B-v3/include/bits/memory_resource.h#L61
 *  -
 * https://github.com/mmp/pbrt-v4/blob/39e01e61f8de07b99859df04b271a02a53d9aeb2/src/pbrt/util/pstd.h#L483
 * @tparam Tp The type of the object to allocate.
 */
template <typename Tp>
class polymorphic_allocator {
public:
  using value_type = Tp;

  polymorphic_allocator() noexcept {
    extern memory_resource *get_default_resource();
    m_resource = get_default_resource();
  }

  polymorphic_allocator(memory_resource *r) noexcept : m_resource(r) {} // NOLINT(*-explicit-constructor)

  polymorphic_allocator(polymorphic_allocator const &other) = default;

  template <typename U>
  // ReSharper disable once CppNonExplicitConvertingConstructor
  polymorphic_allocator(polymorphic_allocator<U> const &other) noexcept : m_resource(other.resource()) {} // NOLINT(*-explicit-constructor)

  polymorphic_allocator &operator=(const polymorphic_allocator &other) = delete;

  [[nodiscard]]
  Tp *allocate(size_t n) {
    return static_cast<Tp *>(m_resource->allocate(n * sizeof(Tp), alignof(Tp)));
  }

  void deallocate(Tp *p, size_t n) {
    m_resource->deallocate(p, n * sizeof(Tp), alignof(Tp));
  }

  [[nodiscard]]
  void *allocate_bytes(size_t n) {
    return m_resource->allocate(n, alignof(std::max_align_t));
  }

  void deallocate_bytes(void *p, size_t n) {
    m_resource->deallocate(p, n, alignof(std::max_align_t));
  }

  template <typename Up>
  [[nodiscard]]
  Up *allocate_object(size_t n = 1) {
    return static_cast<Up *>(allocate_bytes(n * sizeof(Up), alignof(Up)));
  }

  template <typename Up>
  void deallocate_object(Up *p, size_t n = 1) {
    deallocate_bytes(p, n);
  }

  template <typename Up, typename... Args>
  void construct(Up *p, Args &&... args) {
    new (p) Up(std::forward<Args>(args)...);
  }

  template <class Up, class ...Args>
  Up *new_object(Args &&...args) {
    Up *p = allocate_object<Up>();
    construct(p, std::forward<Args>(args)...);
    return p;
  }

  template <class Up>
  void delete_object(Up *p) {
    p->~Up();
    deallocate_object(p);
  }

  [[nodiscard]]
  memory_resource *resource() const noexcept { return m_resource; }

private:
  memory_resource *m_resource;
};

template <typename Tp1, typename Tp2>
[[nodiscard]]
bool operator==(const polymorphic_allocator<Tp1> &a, const polymorphic_allocator<Tp2> &b) noexcept {
  return a.resource() == b.resource();
}

template <typename Tp1, typename Tp2>
[[nodiscard]]
bool operator!=(const polymorphic_allocator<Tp1> &a, const polymorphic_allocator<Tp2> &b) noexcept {
  return !(a == b);
}

} // namespace jtx::pmr
