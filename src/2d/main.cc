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

int main(const int argc, const char* argv[]) {
  logger::open(title);
  logger::logDebug("Start. Version {}.{}")(VERSION_MAJOR, VERSION_MINOR);

  if (!glfwInit()) {
    logger::logError("Cannot initiate glfw")();
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  utils::defer defer{ utils::sequence(glfwTerminate, logger::logDebug("Exit")) };

  GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    logger::logError("Imposible to create window")();
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, onWindowSizeChanged);
  glfwSetKeyCallback(window, onKeyPress);

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    logger::logError("Impossible to load OpenGL functions")();
    return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}
