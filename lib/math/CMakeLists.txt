add_library(math STATIC Matrix3x3.cc)
target_compile_features(math PRIVATE cxx_std_20)