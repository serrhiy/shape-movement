#include <assert.h>

#include <utils/functional.hh>

int main(const int argc, const char* argv[]) {
  int number = 0;
  const auto inc = [&number]() { number++; };

  utils::sequence()();

  utils::sequence(inc)();
  assert(number == 1 && "utils::sequence does not work with 1 function");

  utils::sequence(inc, inc, inc)();
  assert(number == 4 && "utils::sequence does not work with multiple functions");

  return 0;
}
