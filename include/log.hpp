#pragma once

#include <format>
#include <iostream>
#include <string_view>

enum class LOG_LEVEL {
  INFO,
  ERROR,
  NOTHING,
};

class LOG {
  LOG_LEVEL level{LOG_LEVEL::ERROR};

  static LOG &get_instance() {
    static LOG instance;
    return instance;
  }

  LOG() = default;

  static void LOG_MESSAGE(const std::string_view message) {
    std::cerr << std::format("{}", message);
  }

public:
  static void SET_LEVEL(const LOG_LEVEL log_level) {
    get_instance().level = log_level;
  }

  static void operator()(const std::string_view message,
                         const LOG_LEVEL log_level) {
    auto &instance = get_instance();

    if (log_level <= instance.level)
      LOG_MESSAGE(message);
  }
};

static inline void INFO(const std::string_view message) {
  LOG::operator()(message, LOG_LEVEL::INFO);
}
static inline void ERROR(const std::string_view message) {
  LOG::operator()(message, LOG_LEVEL::ERROR);
}
