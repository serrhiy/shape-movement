add_library(math STATIC Matrix.cc)
target_compile_features(math PRIVATE cxx_std_23)