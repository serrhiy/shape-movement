#include "Matrix.hh"

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace math {
Matrix::Matrix(std::vector<float> data, unsigned rows, unsigned cols)
    : data{std::move(data)}, rows{rows}, cols{cols} {}

Matrix::Matrix(std::initializer_list<std::initializer_list<float>> matrix) {
  if (matrix.size() == 0) {
    throw std::runtime_error{"Inpossible to create empty matrix"};
  }
  rows = matrix.size();
  cols = matrix.begin()->size();
  data.resize(rows * cols);
  float* data_pointer = data.data();
  for (const std::initializer_list<float>& row : matrix) {
    if (row.size() != cols) {
      throw std::runtime_error{"All rows must have the same number of columns"};
    }
    std::copy(row.begin(), row.end(), data_pointer);
    data_pointer += cols;
  }
}

unsigned Matrix::getRows() const { return rows; }
unsigned Matrix::getCols() const { return cols; }

Matrix Matrix::scale3x3(const float x, const float y) {
  return Matrix{{
      {x, 0, 0},
      {0, y, 0},
      {0, 0, 1},
  }};
}

Matrix Matrix::scale3x3(const float n) { return scale3x3(n, n); }

Matrix Matrix::translate3x3(const float x, const float y) {
  return Matrix{{{1, 0, 0}, {0, 1, 0}, {x, y, 1}}};
}

Matrix Matrix::scale4x4(const float x, const float y, const float z) {
  return Matrix{{
      {x, 0, 0, 0},
      {0, y, 0, 0},
      {0, 0, z, 0},
      {0, 0, 0, 1},
  }};
}

Matrix Matrix::scale4x4(const float n) { return scale4x4(n, n, n); }

Matrix Matrix::translate4x4(const float x, const float y, const float z) {
  return Matrix{{
      {1, 0, 0, 0},
      {0, 1, 0, 0},
      {0, 0, 1, 0},
      {x, y, z, 1},
  }};
}

Matrix Matrix::rotate4x4x(const float theta) {
  return Matrix{{{1, 0, 0, 0},
                 {0, std::cos(theta), std::sin(theta), 0},
                 {0, -std::sin(theta), std::cos(theta), 0},
                 {0, 0, 0, 1}}};
}

Matrix Matrix::rotate4x4y(const float theta) {
  return Matrix{{{std::cos(theta), 0, -std::sin(theta), 0},
                 {0, 1, 0, 0},
                 {std::sin(theta), 0, std::cos(theta), 0},
                 {0, 0, 0, 1}}};
}

Matrix Matrix::rotate4x4z(const float theta) {
  return Matrix{{{std::cos(theta), std::sin(theta), 0, 0},
                 {-std::sin(theta), std::cos(theta), 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}}};
}

Matrix Matrix::rotate4x4(float x, float y, float z, float theta) {
  const float sina = std::sin(theta);
  const float cosa = std::cos(theta);
  std::vector<float> matrix(16);
  matrix[0] = cosa + x * x * (1 - cosa);
  matrix[1] = y * x * (1 - cosa) + z * sina;
  matrix[2] = z * x * (1 - cosa) - y * sina;
  matrix[3] = 0.0f;
  matrix[4] = x * y * (1 - cosa) - z * sina;
  matrix[5] = cosa + y * y * (1 - cosa);
  matrix[6] = z * y * (1 - cosa) + x * sina;
  matrix[7] = 0.0f;
  matrix[8] = x * z * (1 - cosa) + y * sina;
  matrix[9] = y * z * (1 - cosa) - x * sina;
  matrix[10] = cosa + z * z * (1 - cosa);
  matrix[11] = 0.0f;
  matrix[12] = 0.0f;
  matrix[13] = 0.0f;
  matrix[14] = 0.0f;
  matrix[15] = 1.0f;
  return Matrix{matrix, 4, 4};
}

Matrix Matrix::perspective(float fov, float aspect, float near, float far) {
  const float top = near * std::tan(fov / 2.0f);
  const float right = top * aspect;
  return Matrix{{{near / right, 0, 0, 0},
                 {0, near / top, 0, 0},
                 {0, 0, -(far + near) / (far - near), -1},
                 {0, 0, -(2 * far * near) / (far - near), 0}}};
}

Matrix Matrix::operator*(const Matrix& other) const {
  if (getCols() != other.getRows()) {
    throw std::runtime_error{"Invalid matrix size for multiplication"};
  }

  const unsigned result_rows = getRows();
  const unsigned result_cols = other.getCols();
  std::vector<float> result_data(result_rows * result_cols, 0.f);

  for (unsigned i = 0; i < result_rows; i++) {
    for (unsigned j = 0; j < result_cols; j++) {
      float sum = 0.0f;
      for (unsigned k = 0; k < getCols(); k++) {
        sum += data[i * cols + k] * other.data[k * other.cols + j];
      }
      result_data[i * result_cols + j] = sum;
    }
  }

  return Matrix{std::move(result_data), result_rows, result_cols};
}

const float* Matrix::pointer() const { return data.data(); };
}  // namespace math
