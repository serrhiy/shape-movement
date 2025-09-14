find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(3d main.cc)
target_link_libraries(3d PRIVATE glfw glad::glad utils logger math shader)
target_include_directories(3d PRIVATE "${PROJECT_BINARY_DIR}")
target_compile_features(3d PRIVATE cxx_std_23)
set_target_properties(3d PROPERTIES CXX_EXTENSIONS OFF)

add_custom_target(copy_3d_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            ${CMAKE_CURRENT_BINARY_DIR}/shaders
    COMMENT "Copying shaders 3d..."
)

add_dependencies(3d copy_3d_shaders)

set(SHADERS_PATH "${CMAKE_CURRENT_BINARY_DIR}/shaders")
configure_file(resources.hh.in "${CMAKE_CURRENT_BINARY_DIR}/resources.hh")
target_include_directories(3d PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
