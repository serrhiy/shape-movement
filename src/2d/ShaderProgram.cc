#include "ShaderProgram.hh"

#include <string>
#include <utility>
#include <glad/glad.h>
#include <stdexcept>

void ShaderProgram::deleteProgram() {
  if (shader_program != 0) {
    glDeleteProgram(shader_program);
    shader_program = 0;
  }
}

ShaderProgram::ShaderProgram(const VertexShader& vertex, const FragmentShader& fragment)
  : shader_program{ glCreateProgram() },
    vertex_object{ vertex.id() },
    fragment_object{ fragment.id() } {
  if (shader_program == 0) {
    throw std::runtime_error{ "Error while allocating shader program" };
  }
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
  : shader_program{ other.shader_program },
    vertex_object{ other.vertex_object },
    fragment_object{ other.fragment_object } {
  other.shader_program = 0;
  other.vertex_object = 0;
  other.fragment_object = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) {
  if (this != &other) {
    deleteProgram();
    shader_program = vertex_object = fragment_object = 0;
    std::swap(shader_program, other.shader_program);
    std::swap(vertex_object, other.vertex_object);
    std::swap(fragment_object, other.fragment_object);
  }
  return *this;
}

ShaderProgram::~ShaderProgram() { deleteProgram(); }

void ShaderProgram::attach() {
  if (shader_program == 0) return;

  std::string error_message_bufer(error_buffer_size, '\0');
  int error_flag = 0;

  glAttachShader(shader_program, vertex_object);
  glAttachShader(shader_program, fragment_object);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &error_flag);
  if (!error_flag) {
    glGetProgramInfoLog(shader_program, error_buffer_size, nullptr, error_message_bufer.data());
    throw std::runtime_error{ "Error while linking shader program:\n" + error_message_bufer };
  }
}

void ShaderProgram::use() {
  if (shader_program != 0) glUseProgram(shader_program);
}
