#pragma once

#include <functional>

namespace utils {
  std::function<void()> sequence(auto... functions) {
    return [=]() { (functions(), ...); };
  }
}
