#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>
#include <filesystem>
#include <exception>
#include <stdexcept>
#include <iostream>

#include <logger/core.hh>
#include <utils/defer.hh>
#include <version.hh>
#include <resources.hh>

#include "Shader.hh"
#include "ShaderProgram.hh"

constexpr unsigned height = 600;
constexpr unsigned width = 800;
constexpr const char* title = "Shape movement 2D";

constexpr const char* vertex_shader_path = SHADERS_PATH "/vertex.vert";
constexpr const char* fragment_shader_path = SHADERS_PATH "/fragment.frag";

constexpr std::array<float, 18> vertices{
   0.5f,  0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
  -0.5f,  0.5f, 0.0f,

   0.5f, -0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  -0.5f,  0.5f, 0.0f
};

void onWindowSizeChanged(GLFWwindow* window, int width, int height) {
  logger::logDebug("Changed window size: {}x{}")(width, height);
  glViewport(0, 0, width, height);
}

void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
  logger::logDebug("Key action. Key: {}, action: {}")(key, action);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void start() {
  if (!glfwInit()) {
    throw std::runtime_error{ "Cannot initiate glfw" };
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  utils::defer defer{ glfwTerminate };

  GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    throw std::runtime_error{ "Imposible to create window" };
  }

  glfwSetFramebufferSizeCallback(window, onWindowSizeChanged);
  glfwSetKeyCallback(window, onKeyPress);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::runtime_error{ "Impossible to load OpenGL functions" };
  }

  unsigned vertex_array_object = 0;
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);

  unsigned vertex_buffer_object = 0;
  glGenBuffers(1, &vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  VertexShader vertex_shader{ vertex_shader_path };
  FragmentShader fragment_shader{ fragment_shader_path };
  vertex_shader.compile();
  fragment_shader.compile();

  ShaderProgram shader_program{ vertex_shader, fragment_shader };
  shader_program.attach();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.145f, 0.09f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_program.use();
    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

int main(const int argc, const char* argv[]) {
  try {
    logger::open(title);
    logger::logDebug("Start. Version {}.{}")(VERSION_MAJOR, VERSION_MINOR);
    utils::defer defer{ logger::logDebug("Exit") };

    try {
      start();
      return 0;
    }
    catch(const std::exception& exception) {
      logger::logError(exception.what())();
    }
  }
  catch(const std::exception& exception) {
    std::cerr << exception.what() << '\n';
  }
  return 1;
}
