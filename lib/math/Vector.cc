#include "Vector.hh"

namespace math {
Vector3::Vector3(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} {}

Vector3::Vector3(float x, float y, float z) : Vector3{x, y, z, 1} {}

Vector2::Vector2(float x, float y, float w) : x{x}, y{y}, w{w} {}
Vector2::Vector2(float x, float y) : Vector2{x, y, 1} {}
}  // namespace math
