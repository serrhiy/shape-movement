add_library(utils-interface INTERFACE)
target_compile_features(utils-interface INTERFACE cxx_std_20)
target_include_directories(utils-interface INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(utils STATIC fs.cc)
target_compile_features(utils PRIVATE cxx_std_20)
target_link_libraries(utils PUBLIC utils-interface)
