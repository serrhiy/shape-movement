find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
add_executable(2d main.cc)

target_link_libraries(2d PRIVATE glfw glad::glad utils logger math shader)
target_include_directories(2d PRIVATE "${PROJECT_BINARY_DIR}")
target_compile_features(2d PRIVATE cxx_std_23)
set_target_properties(2d PROPERTIES CXX_EXTENSIONS OFF)

add_custom_target(copy_2d_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            ${CMAKE_CURRENT_BINARY_DIR}/shaders
    COMMENT "Copying shaders 2d..."
)

add_dependencies(2d copy_2d_shaders)

set(SHADERS_PATH "${CMAKE_CURRENT_BINARY_DIR}/shaders")
configure_file(resources.hh.in "${CMAKE_CURRENT_BINARY_DIR}/resources.hh")
target_include_directories(2d PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
