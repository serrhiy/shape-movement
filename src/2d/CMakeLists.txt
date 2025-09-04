find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
add_executable(main main.cc)

target_link_libraries(main PRIVATE glfw glad::glad utils logger)
target_include_directories(main PRIVATE "${PROJECT_BINARY_DIR}")
target_compile_features(main PRIVATE cxx_std_20)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)
