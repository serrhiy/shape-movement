find_package(glad CONFIG REQUIRED)

add_library(shader-interface INTERFACE Shader.hh)
target_compile_features(shader-interface INTERFACE cxx_std_23)
target_include_directories(shader-interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_link_libraries(shader-interface INTERFACE glad::glad utils)

add_library(shader SHARED ShaderProgram.cc)
target_compile_features(shader PRIVATE cxx_std_23)
target_link_libraries(shader PUBLIC shader-interface)
