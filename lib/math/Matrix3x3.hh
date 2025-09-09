#pragma once

#include <array>

namespace math {
  class Matrix3x3 {
    std::array<float, 9> data;

    Matrix3x3(std::array<float, 9>&& data);

  public:
    static Matrix3x3 scale(const float x, const float y);
    static Matrix3x3 scale(const float n);
    static Matrix3x3 translate(const float x, const float y);

    Matrix3x3 operator*(const Matrix3x3& other) const;

    const float* pointer() const;
  };
}
