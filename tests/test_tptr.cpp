#include <catch2/catch_test_macros.hpp>
#include <jtxlib/util/taggedptr.hpp>

// Simple CRTP class to test tagged pointer dispatch
using namespace jtx;

template<typename Derived>
class BaseShape {
public:
  [[nodiscard]] int code() const {
    return static_cast<const Derived *>(this)->code();
  }
};

class Circle : public BaseShape<Circle> {
public:
  Circle() = default;

  [[nodiscard]] int code() const {
    return 1;
  }
};

class Square : public BaseShape<Square> {
public:
  Square() = default;

  int code() const {
    return 2;
  }
};

TEST_CASE("TaggedPtr default constructor", "[TaggedPtr]") {
  Square square{};
  Circle circle{};

  SECTION("Square: tag == 1") {
      TaggedPtr<Square, Circle> ptr{&square};
      REQUIRE(ptr.getTag() == 1);
      REQUIRE(ptr.getPtr() == &square);
  }

  SECTION("Circle: tag == 2") {
    TaggedPtr<Square, Circle> ptr{&circle};
    REQUIRE(ptr.getTag() == 2);
    REQUIRE(ptr.getPtr() == &circle);
  }

  SECTION("nullptr: tag == 0") {
    TaggedPtr<Square, Circle> ptr{nullptr};
    REQUIRE(ptr.getTag() == 0);
    REQUIRE(ptr.getPtr() == nullptr);
  }
}


TEST_CASE("TaggedPtr dispatch", "[TaggedPtr]") {
  SECTION("Square: code == 2") {
    Square square{};
    TaggedPtr<Square, Circle> ptr{&square};
    auto code = [&](auto p) { return p->code(); };
    auto i = ptr.dispatch(code);
    REQUIRE(i == 2);
  }

  SECTION("Circle: code == 1") {
    Circle circle{};
    TaggedPtr<Square, Circle> ptr{&circle};
    auto code = [&](auto p) { return p->code(); };
    auto i = ptr.dispatch(code);
    REQUIRE(i == 1);
  }
}