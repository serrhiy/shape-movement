#pragma once

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <string_view>
#include <filesystem>
#include <string>
#include <source_location>
#include <syslog.h>

namespace logger {
  void open(std::string_view name) {
    openlog(name.data(), LOG_CONS | LOG_PERROR | LOG_PID, LOG_USER);
  }

  void log(int level, std::string_view format, const std::source_location& location, auto&&... args) {
    const std::string message = fmt::format(
      fmt::runtime(format),
      std::forward<decltype(args)>(args)...
    );
    const std::filesystem::path full_path = location.file_name();
    syslog(level, "%s:%d %s", full_path.filename().c_str(), location.line(), message.c_str());
  }
  
  void logInfo(std::string_view format, auto&&... args,
      const std::source_location& location = std::source_location::current()) {
    log(LOG_INFO, format, location, std::forward<decltype(args)>(args)...);
  }

  void logWarning(std::string_view format, auto&&... args,
      const std::source_location& location = std::source_location::current()) {
    log(LOG_WARNING, format, location, std::forward<decltype(args)>(args)...);
  }

  void logError(std::string_view format, auto&&... args,
      const std::source_location& location = std::source_location::current()) {
    log(LOG_ERR, format, location, std::forward<decltype(args)>(args)...);
  }

  void logDebug(std::string_view format, auto&&... args,
      const std::source_location& location = std::source_location::current()) {
    log(LOG_DEBUG, format, location, std::forward<decltype(args)>(args)...);
  };
}
