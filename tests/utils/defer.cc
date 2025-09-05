#include <assert.h>
#include <functional>

#include <utils/defer.hh>

int main(const int argc, const char* argv[]) {
  int number = 0;
  const auto inc1 = [&number]() { number++; };
  const auto inc2 = [](int& number) {
    number++;
  };

  {
    utils::defer d1{ inc1 };
  }
  assert(number == 1 && "Function is not called in the destructor");

  {
    utils::defer d1{ inc2, std::ref(number) };
  }

  assert(number == 2 && "Function with parameter is not called in the destructor");

  return 0;
}
