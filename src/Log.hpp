#pragma once
#include <iostream>
#include <fmt/format.h>

struct Log {
  enum Level {
              DEBUG, INFO, ERROR };

  static Level level;

  template<typename... Args>
  static void info(const char *s, const Args&... args)
{
  log(Log::INFO, s, args...);
}

  template<typename... Args>
  static void debug(const char *s, const Args&... args)
{
  log(Log::DEBUG, s, args...);
}

  template<typename... Args>
  static void error(const char *s, const Args&... args)
{
  
  log(Log::ERROR, s, args...);
}

  static const char *name(const Level &level)
  {
    return (const char *[]) {
      "debug", "info", "error"
        }[level];
  }

  template<typename... Args>
  static void log(const Level &level,
                  const char *s,
                  const Args&... args)
    
{
  if (level >= Log::level) {
    std::cerr << "[" << Log::name(level) << "] "
              << fmt::format(s, args...) << std::endl;
  }
}
};
