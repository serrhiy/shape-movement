find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
add_executable(main main.cc)
target_link_libraries(main PRIVATE glfw glad::glad)
