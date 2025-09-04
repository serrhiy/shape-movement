find_package(fmt CONFIG REQUIRED)

add_library(logger INTERFACE)
target_link_libraries(logger INTERFACE fmt::fmt)
target_include_directories(logger INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_compile_features(logger INTERFACE cxx_std_20)
