find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
add_executable(main main.cc ShaderProgram.cc)

target_link_libraries(main PRIVATE glfw glad::glad utils logger)
target_include_directories(main PRIVATE "${PROJECT_BINARY_DIR}")
target_compile_features(main PRIVATE cxx_std_20)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            ${CMAKE_CURRENT_BINARY_DIR}/shaders
    COMMENT "Copying shaders..."
)

add_dependencies(main copy_shaders)

set(SHADERS_PATH "${CMAKE_CURRENT_BINARY_DIR}/shaders")
configure_file(resources.hh.in "${CMAKE_CURRENT_BINARY_DIR}/resources.hh")
target_include_directories(main PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
