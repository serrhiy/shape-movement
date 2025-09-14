#include "fs.hh"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace utils {
std::string readFile(const std::filesystem::path& path) {
  std::ifstream input_file_stream{path};
  if (!input_file_stream.is_open()) {
    throw std::runtime_error{"Cannot open " + path.string()};
  }
  std::ostringstream output_string_stream;
  output_string_stream << input_file_stream.rdbuf();
  if (output_string_stream.fail() || output_string_stream.fail()) {
    throw std::runtime_error{"Error occured while reading " + path.string()};
  }
  return output_string_stream.str();
}
}  // namespace utils
