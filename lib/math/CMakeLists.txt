add_library(math SHARED Matrix.cc Vector.cc)
target_compile_features(math PRIVATE cxx_std_23)