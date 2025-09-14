#pragma once

#include <filesystem>
#include <string>

namespace utils {
std::string readFile(const std::filesystem::path& path);
};
