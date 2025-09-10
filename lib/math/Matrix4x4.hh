#pragma once

#include <array>

namespace math {
  class Matrix4x4 {
    std::array<float, 16> data;

    Matrix4x4(std::array<float, 16>&& data);

  public:
    static Matrix4x4 translate(const float x, const float y, const float z);
    static Matrix4x4 scale(const float x, const float y, const float z);
    static Matrix4x4 rotate(const float a, const float b, const float t);

    Matrix4x4 operator*(const Matrix4x4& other);
  };
}
