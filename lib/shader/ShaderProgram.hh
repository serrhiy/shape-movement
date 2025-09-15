#pragma once

#include <string_view>

#include "Shader.hh"

class ShaderProgram {
  unsigned shader_program;
  unsigned vertex_object;
  unsigned fragment_object;

  static constexpr unsigned error_buffer_size = 512;

  void deleteProgram();

  unsigned getLocation(std::string_view location);

 public:
  ShaderProgram() = delete;
  ShaderProgram(const VertexShader& vertex, const FragmentShader& fragment);

  ShaderProgram(const ShaderProgram&) = delete;
  ShaderProgram& operator=(const ShaderProgram&) = delete;

  ShaderProgram(ShaderProgram&& other) noexcept;
  ShaderProgram& operator=(ShaderProgram&&);

  ~ShaderProgram();

  void attach();
  void use();

  void setUniformMatrix3x3(std::string_view location, const float* data);
  void setUniformVector3(std::string_view location, float x, float y, float z);
};
