#pragma once

namespace math {
struct Vector2 {
  float x, y, w;

  Vector2(float x, float y, float w);
  Vector2(float x, float y);
};

struct Vector3 {
  float x, y, z, w;

  Vector3(float x, float y, float z, float w);
  Vector3(float x, float y, float z);
};
};  // namespace math