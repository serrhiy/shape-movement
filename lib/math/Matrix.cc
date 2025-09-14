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

Matrix Matrix::scale4x4(const float n) {
  return scale4x4(n, n, n);
}

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
