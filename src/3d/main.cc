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
#include <math/Vector.hh>
#include <numbers>
#include <resources.hh>
#include <shader/Shader.hh>
#include <shader/ShaderProgram.hh>
#include <stdexcept>
#include <utils/defer.hh>
#include <version.hh>

constexpr float fpi = std::numbers::pi_v<float>;

constexpr unsigned height = 800;
constexpr unsigned width = 800;
constexpr const char* title = "Shape movement 3D";

constexpr const char* vertex_shader_path = SHADERS_PATH "/vertex.vert";
constexpr const char* fragment_shader_path = SHADERS_PATH "/fragment.frag";

constexpr float start_angle = fpi / 2;
constexpr float low = -1;
constexpr float high = 1;

const math::Vector3 base1{std::cos(start_angle), low, std::sin(start_angle)};
const math::Vector3 base2{std::cos(start_angle + 2.f * fpi / 3.f), low,
                          std::sin(start_angle + 2 * fpi / 3.f)};
const math::Vector3 base3{std::cos(start_angle - 2 * fpi / 3.f), low,
                          std::sin(start_angle - 2 * fpi / 3.f)};
const math::Vector3 top{(base1.x + base2.x + base3.x) / 3.f, high,
                        (base1.z + base2.z + base3.z) / 3.f};

const math::Matrix vertices{
    {base1.x, base1.y, base1.z, 1}, {base2.x, base2.y, base2.z, 1},
    {base3.x, base3.y, base3.z, 1},

    {base1.x, base1.y, base1.z, 1}, {base3.x, base3.y, base3.z, 1},
    {top.x, top.y, top.z, 1},

    {base3.x, base3.y, base3.z, 1}, {base2.x, base2.y, base2.z, 1},
    {top.x, top.y, top.z, 1},

    {base2.x, base2.y, base2.z, 1}, {base1.x, base1.y, base1.z, 1},
    {top.x, top.y, top.z, 1},
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

  glVertexAttribPointer(0, vertices.getCols(), GL_FLOAT, GL_FALSE,
                        vertices.getCols() * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.145f, 0.09f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float x = static_cast<float>(glfwGetTime());

    constexpr float max = 20.f, min = 0.1f;

    const math::Matrix rotate = math::Matrix::rotate4x4(0, 1, 0, x);
    const math::Matrix translate = math::Matrix::translate4x4(
        2 * cos(x / 2 - fpi), 0,
        -(max / 2) * sin(x / 2 - fpi) - (max / 2) - 3.5);
    const math::Matrix projection = math::Matrix::perspective(
        std::numbers::pi / 4, static_cast<double>(width) / height, min, max);

    const math::Matrix position = vertices * rotate * translate * projection;

    shader_program.use();
    glBindVertexArray(vertex_array_object);
    glBufferSubData(GL_ARRAY_BUFFER, 0, items_number * sizeof(float),
                    position.pointer());

    float r = std::fabs(std::sin(x));
    float g = std::fabs(std::sin(x + 2.0f * fpi / 3.0f));
    float b = std::fabs(std::sin(x + 4.0f * fpi / 3.0f));
    shader_program.setUniformVector3("color", r, g, b);

    glDrawArrays(GL_TRIANGLES, 0, vertices.getRows());

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
