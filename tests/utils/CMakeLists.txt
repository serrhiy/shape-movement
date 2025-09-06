function(addTest filename testname)
  add_executable(${testname} ${filename})
  target_link_libraries(${testname} utils)
  add_test(NAME ${testname} COMMAND ${testname})
endfunction()

addTest(defer.cc utils_defer_test)
addTest(sequence.cc utils_sequence_test)
