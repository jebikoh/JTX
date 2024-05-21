#pragma once

#include <cblas.h>
#include <cmath>

namespace JTX::Util {
enum class Axis { X = 0, Y = 1, Z = 2 };

/**
 * @brief A 4x4 matrix
 *
 * This class represents a 4x4 matrix that can be used to represent affine
 * transformations in 3D space. The matrix is stored in ROW-MAJOR order.
 */
class Mat4 {
public:
  float data[4][4]{};

  /**
   * @brief Constructs a 4x4 identity matrix
   */
  Mat4();
  Mat4(float d00, float d01, float d02, float d03, float d10, float d11,
       float d12, float d13, float d20, float d21, float d22, float d23,
       float d30, float d31, float d32, float d33);
  ~Mat4() = default;

  bool operator==(const Mat4 &other) const;
  bool operator!=(const Mat4 &other) const;
  inline float *operator[](int index) { return data[index]; };
  inline const float *operator[](int index) const { return data[index]; };

  /**
   * @brief Returns a rotation affine transformation matrix
   * @param rad Angle in radians
   * @param axis Axis of rotation.
   * @return Mat4 Rotation matrix
   */
  static Mat4 rotation(float rad, Axis axis);

  /**
   * @brief Returns a translation affine transformation matrix
   * @param x X translation
   * @param y Y translation
   * @param z Z translation
   * @return Mat4 Translation matrix
   */
  static Mat4 translation(float x, float y, float z);

  /**
   * @brief Returns a scaling affine transformation matrix
   * @param x X scale
   * @param y Y scale
   * @param z Z scale
   * @return
   */
  static Mat4 scale(float x, float y, float z);

  /**
   * @brief Performs matrix multiplication between two 4x4 matrices
   * @param m1 Left matrix
   * @param m2 Right matrix
   * @return Mat4 Result of the matrix multiplication
   */
  static Mat4 matmul(const Mat4 &m1, const Mat4 &m2);
  /**
   * @brief Performs matrix multiplication between two 4x4 matrices
   * @param other Right matrix
   * @return Mat4 Result of the matrix multiplication
   */
  Mat4 operator*(const Mat4 &other) const;
};
} // namespace JTX::Util