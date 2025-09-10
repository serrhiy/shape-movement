#include "Matrix3x3.hh"

#include <array>

namespace math {
  Matrix3x3::Matrix3x3(std::array<float, 9>&& data): data{ data } { }

  Matrix3x3 Matrix3x3::scale(const float x, const float y) {
    return Matrix3x3{{
       x, 0, 0,
       0, y, 0,
       0, 0, 1,
    }};
  }

  Matrix3x3 Matrix3x3::scale(const float n) { return scale(n, n); }

  Matrix3x3 Matrix3x3::translate(const float x, const float y) {
    return Matrix3x3{{
       1, 0, x,
       0, 1, y,
       0, 0, 1,
    }};
  }

  Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
    const std::array<float, 9>& a = this->data;
    const std::array<float, 9>& b = other.data;
    return Matrix3x3{{
      a[0] * b[0] + a[1] * b[3] + a[2] * b[6],
      a[0] * b[1] + a[1] * b[4] + a[2] * b[7],
      a[0] * b[2] + a[1] * b[5] + a[2] * b[8],

      a[3] * b[0] + a[4] * b[3] + a[5] * b[6],
      a[3] * b[1] + a[4] * b[4] + a[5] * b[7],
      a[3] * b[2] + a[4] * b[5] + a[5] * b[8],

      a[6] * b[0] + a[7] * b[3] + a[8] * b[6],
      a[6] * b[1] + a[7] * b[4] + a[8] * b[7],
      a[6] * b[2] + a[7] * b[5] + a[8] * b[8],
    }};
  }

  const float* Matrix3x3::pointer() const { return data.data(); }
}
