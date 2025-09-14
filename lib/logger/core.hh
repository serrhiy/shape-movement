#pragma once

#include <syslog.h>

#include <filesystem>
#include <format>
#include <iostream>
#include <source_location>
#include <string>
#include <string_view>

namespace logger {
using src_loc = std::source_location;

void open(std::string_view name) {
  openlog(name.data(), LOG_CONS | LOG_PERROR | LOG_PID, LOG_USER);
}

void log(int level, const src_loc& location, std::string_view format,
         std::format_args&& args) {
  const std::string message = std::vformat(format, args);
  const std::filesystem::path full_path = location.file_name();
  syslog(level, "%s:%d %s", full_path.filename().c_str(), location.line(),
         message.c_str());
}

auto logInfo(std::string_view format,
             const src_loc& location = src_loc::current()) {
  return [format, location](auto&&... args) {
    log(LOG_INFO, location, format, std::make_format_args(args...));
  };
}

auto logWarning(std::string_view format,
                const src_loc& location = src_loc::current()) {
  return [format, location](auto&&... args) {
    log(LOG_WARNING, location, format, std::make_format_args(args...));
  };
}

auto logError(std::string_view format,
              const src_loc& location = src_loc::current()) {
  return [format, location](auto&&... args) {
    log(LOG_ERR, location, format, std::make_format_args(args...));
  };
}

auto logDebug(std::string_view format,
              const src_loc& location = src_loc::current()) {
  return [format, location](auto&&... args) {
    log(LOG_DEBUG, location, format, std::make_format_args(args...));
  };
}
}  // namespace logger
