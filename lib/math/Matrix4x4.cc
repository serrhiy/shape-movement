#include "Matrix4x4.hh"

#include <array>

namespace math {
  Matrix4x4::Matrix4x4(std::array<float, 16>&& data): data{ data } {}

  Matrix4x4 Matrix4x4::translate(const float x, const float y, const float z) {
    return Matrix4x4{{
      1, 0, 0, x,
      0, 1, 0, y,
      0, 0, 1, z,
      0, 0, 0, 1,
    }};
  }

  Matrix4x4 Matrix4x4::scale(const float x, const float y, const float z) {
    return Matrix4x4{{
      x, 0, 0, 0,
      0, y, 0, 0,
      0, 0, z, 0,
      0, 0, 0, 1,
    }};
  }

  Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) {
    const std::array<float, 16>& a = this->data;
    const std::array<float, 16>& b = other.data;
    return Matrix4x4{{
      a[0] * b[0] + a[1] * b[4] + a[2] * b[8]  + a[3] * b[12],
      a[0] * b[1] + a[1] * b[5] + a[2] * b[9]  + a[3] * b[13],
      a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
      a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],

      a[4] * b[0] + a[5] * b[4] + a[6] * b[8]  + a[7] * b[12],
      a[4] * b[1] + a[5] * b[5] + a[6] * b[9]  + a[7] * b[13],
      a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
      a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],

      a[8]  * b[0] + a[8]  * b[4] + a[8]  * b[8]  + a[8]  * b[12],
      a[9]  * b[1] + a[9]  * b[5] + a[9]  * b[9]  + a[9]  * b[13],
      a[10] * b[2] + a[10] * b[6] + a[10] * b[10] + a[10] * b[14],
      a[11] * b[3] + a[11] * b[7] + a[11] * b[11] + a[11] * b[15],
    }};
  }
}
