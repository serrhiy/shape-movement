add_library(logger INTERFACE)
target_include_directories(logger INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/..")
target_compile_features(logger INTERFACE cxx_std_23)
