#pragma once

#include <glad/glad.h>

#include <utils/fs.hh>
#include <iostream>

template <unsigned shader_type>
class Shader {
  unsigned object;
  std::filesystem::path path;

  static constexpr unsigned error_buffer_size = 512;

  void deleteShader() {
    if (object != 0) {
      glDeleteShader(object);
      object = 0;
    }
  }

public:
  Shader() = delete;

  Shader(std::filesystem::path path)
    : object{ glCreateShader(shader_type) },
      path{ std::move(path) } {
    if (object == 0) {
      throw std::runtime_error{ "Error while allocating shader object" };
    }
  }

  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  Shader(Shader&& other) noexcept: object{ other.object }, path{ std::move(other.path) } {
    other.object = 0;
    other.path.clear();
  }

  Shader& operator=(Shader&& other) {
    if (this != &other) {
      deleteShader();
      std::swap(object, other.object);
    }
    return *this;
  }

  ~Shader() { deleteShader(); }

  void compile() {
    if (object == 0) return;

    const std::string sources = utils::readFile(path);
    std::string error_messsage_buffer(error_buffer_size, '\0');
    int error_flag = 0;

    const char* data = sources.data();
    glShaderSource(object, 1, &data, nullptr);
    glCompileShader(object);

    glGetShaderiv(object, GL_COMPILE_STATUS, &error_flag);
    if (!error_flag) {
      glGetShaderInfoLog(object, error_buffer_size, nullptr, error_messsage_buffer.data());
      throw std::runtime_error{
        "Error while compiling " + path.string() + ":\n" + error_messsage_buffer
      };
    }
  }

  unsigned id() const { return object; }
};

using VertexShader = Shader<GL_VERTEX_SHADER>;
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;
