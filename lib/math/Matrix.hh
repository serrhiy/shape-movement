#pragma once

#include <initializer_list>
#include <vector>

namespace math {
class Matrix {
  std::vector<float> data;
  unsigned rows, cols;

  Matrix(std::vector<float> data, unsigned rows, unsigned cols);

 public:
  Matrix(std::initializer_list<std::initializer_list<float>> data);

  unsigned getRows() const;
  unsigned getCols() const;

  static Matrix scale3x3(const float x, const float y);
  static Matrix scale3x3(const float n);
  static Matrix translate3x3(const float x, const float y);

  static Matrix scale4x4(const float x, const float y, const float z);
  static Matrix scale4x4(const float n);
  static Matrix translate4x4(const float x, const float y, const float z);
  static Matrix rotate4x4x(const float theta);
  static Matrix rotate4x4y(const float theta);
  static Matrix rotate4x4z(const float theta);
  static Matrix perspective(float fov, float aspect, float near, float far);

  Matrix operator*(const Matrix& other) const;

  const float* pointer() const;
};
}  // namespace math
