#include "mat4.hpp"

namespace JTX::Util {
Mat4::Mat4() {
  data[0][0] = 1.0f;
  data[0][1] = 0.0f;
  data[0][2] = 0.0f;
  data[0][3] = 0.0f;

  data[1][0] = 0.0f;
  data[1][1] = 1.0f;
  data[1][2] = 0.0f;
  data[1][3] = 0.0f;

  data[2][0] = 0.0f;
  data[2][1] = 0.0f;
  data[2][2] = 1.0f;
  data[2][3] = 0.0f;

  data[3][0] = 0.0f;
  data[3][1] = 0.0f;
  data[3][2] = 0.0f;
  data[3][3] = 1.0f;
}

Mat4::Mat4(float d00, float d01, float d02, float d03, float d10, float d11,
           float d12, float d13, float d20, float d21, float d22, float d23,
           float d30, float d31, float d32, float d33) {
  data[0][0] = d00;
  data[0][1] = d01;
  data[0][2] = d02;
  data[0][3] = d03;

  data[1][0] = d10;
  data[1][1] = d11;
  data[1][2] = d12;
  data[1][3] = d13;

  data[2][0] = d20;
  data[2][1] = d21;
  data[2][2] = d22;
  data[2][3] = d23;

  data[3][0] = d30;
  data[3][1] = d31;
  data[3][2] = d32;
  data[3][3] = d33;
}

bool Mat4::operator==(const Mat4 &other) const {
  for (int j = 0; j < 4; ++j) {
    for (int i = 0; i < 4; ++i) {
      if (data[i][j] != other.data[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool Mat4::operator!=(const Mat4 &other) const { return !(*this == other); }

Mat4 Mat4::rotation(float rad, Axis axis) {
  Mat4 m{};

  float c = std::cosf(rad);
  float s = std::sinf(rad);

  switch (axis) {
  case Axis::X:
    m.data[1][1] = c;
    m.data[1][2] = -s;
    m.data[2][1] = s;
    m.data[2][2] = c;
    break;
  case Axis::Y:
    m.data[0][0] = c;
    m.data[0][2] = s;
    m.data[2][0] = -s;
    m.data[2][2] = c;
    break;
  case Axis::Z:
    m.data[0][0] = c;
    m.data[0][1] = -s;
    m.data[1][0] = s;
    m.data[1][1] = c;
    break;
  }

  return m;
}

Mat4 Mat4::scale(float x, float y, float z) {
  Mat4 m{};

  m.data[0][0] = x;
  m.data[1][1] = y;
  m.data[2][2] = z;

  return m;
}

Mat4 Mat4::translation(float x, float y, float z) {
  Mat4 m{};

  m.data[0][3] = x;
  m.data[1][3] = y;
  m.data[2][3] = z;

  return m;
}

Mat4 Mat4::matmul(const Mat4 &m1, const Mat4 &m2) {
  Mat4 m3{};
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 4, 4, 4, 1.0f,
              (float *)m1.data, 4, (float *)m2.data, 4, 0.0f, (float *)m3.data,
              4);
  return m3;
}

Mat4 Mat4::operator*(const Mat4 &other) const {
  return Mat4::matmul(*this, other);
}
} // namespace JTX::Util
