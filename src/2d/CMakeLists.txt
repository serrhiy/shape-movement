find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
add_executable(main main.cc)

target_link_libraries(main PRIVATE glfw glad::glad)
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/lib")
target_include_directories(main PRIVATE "${PROJECT_BINARY_DIR}")
target_compile_features(main PRIVATE cxx_std_20)
