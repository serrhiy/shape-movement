// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <cmath>
#include <exception>
#include <filesystem>
#include <iostream>
#include <logger/core.hh>
#include <math/Matrix.hh>
#include <resources.hh>
#include <stdexcept>
#include <utils/defer.hh>
#include <version.hh>

#include "Shader.hh"
#include "ShaderProgram.hh"

constexpr unsigned height = 800;
constexpr unsigned width = 800;
constexpr const char* title = "Shape movement 2D";

constexpr const char* vertex_shader_path = SHADERS_PATH "/vertex.vert";
constexpr const char* fragment_shader_path = SHADERS_PATH "/fragment.frag";

constexpr float square_size = 0.25;
constexpr float circle_radius = 0.95f;

const math::Matrix vertices{
    {square_size, square_size, 1},  {square_size, -square_size, 1},
    {-square_size, square_size, 1},

    {square_size, -square_size, 1}, {-square_size, -square_size, 1},
    {-square_size, square_size, 1},
};

void onWindowSizeChanged(GLFWwindow* window, int width, int height) {
  logger::logDebug("Changed window size: {}x{}")(width, height);
  glViewport(0, 0, width, height);
}

void onKeyPress(GLFWwindow* window, int key, int scancode, int action,
                int mods) {
  logger::logDebug("Key action. Key: {}, action: {}")(key, action);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void start() {
  if (!glfwInit()) {
    throw std::runtime_error{"Cannot initiate glfw"};
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  utils::defer defer{glfwTerminate};

  GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    throw std::runtime_error{"Imposible to create window"};
  }

  glfwSetFramebufferSizeCallback(window, onWindowSizeChanged);
  glfwSetKeyCallback(window, onKeyPress);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error{"Impossible to load OpenGL functions"};
  }

  VertexShader vertex_shader{vertex_shader_path};
  FragmentShader fragment_shader{fragment_shader_path};
  vertex_shader.compile();
  fragment_shader.compile();

  ShaderProgram shader_program{vertex_shader, fragment_shader};
  shader_program.attach();

  unsigned vertex_array_object;
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);
  utils::defer defer_vao{glDeleteVertexArrays, 1, &vertex_array_object};

  unsigned vertex_buffer_object;
  glGenBuffers(1, &vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
  const unsigned items_number = vertices.getRows() * vertices.getCols();
  glBufferData(GL_ARRAY_BUFFER, items_number * sizeof(float), nullptr,
               GL_DYNAMIC_DRAW);
  utils::defer defer_vbo{glDeleteBuffers, 1, &vertex_buffer_object};

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.145f, 0.09f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    const float x = static_cast<float>(glfwGetTime());
    const float sinx = std::sin(x);
    const float cosx = std::cos(x);

    const float scale_factor = std::fabs(sinx) + 0.25;

    const float shift_x = cosx * (circle_radius - square_size * scale_factor);
    const float shift_y = sinx * (circle_radius - square_size * scale_factor);

    const math::Matrix translate = math::Matrix::translate3x3(shift_x, shift_y);
    const math::Matrix scale = math::Matrix::scale3x3(scale_factor);
    const math::Matrix position = vertices * scale * translate;

    shader_program.use();
    glBindVertexArray(vertex_array_object);
    glBufferSubData(GL_ARRAY_BUFFER, 0, items_number * sizeof(float),
                    position.pointer());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

int main(const int argc, const char* argv[]) {
  try {
    logger::open(title);
    logger::logDebug("Start. Version {}.{}")(VERSION_MAJOR, VERSION_MINOR);
    utils::defer defer{logger::logDebug("Exit")};

    try {
      start();
      return 0;
    } catch (const std::exception& exception) {
      logger::logError(exception.what())();
    }
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << '\n';
  }
  return 1;
}
