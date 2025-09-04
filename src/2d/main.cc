#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

#include <utils/defer.hh>
#include <utils/functional.hh>
#include <logger/core.hh>
#include <version.hh>

constexpr unsigned height = 600;
constexpr unsigned width = 800;
constexpr const char* title = "Shape movement 2D";

int main(const int argc, const char* argv[]) {
  logger::open(title);
  logger::logDebug("Start. Version {}.{}")(VERSION_MAJOR, VERSION_MINOR);

  if (!glfwInit()) return -1;

  utils::defer defer{ utils::sequence(glfwTerminate, logger::logDebug("Exit")) };

  GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) return -1;

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
