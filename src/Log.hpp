#pragma once
#include <fmt/format.h>
#include <cstdint>
#include <fmt/ostream.h>
#include <iostream>
#include <stdexcept>
#include <string>

#define CHECK(TRACE_HEADER, x) Log::check(TRACE_HEADER, x, #x)

struct AssertionError : public std::runtime_error {
  AssertionError(const std::string &what) : std::runtime_error(what) {
  }
};

struct Log {
  enum Level
  {
    TRACE,
    DEBUG,
    INFO,
    ERROR
  };

  static Level level;

  template <typename... Args>
  static void
  trace(const char *location, const char *s, const Args &... args)
  {

    log(Log::TRACE, location, s, args...);
  }


  template <typename... Args>
  static void
  info(const char *location,
      const char *s,
      const Args &... args)
  {
    log(Log::INFO, location, s, args...);
  }

  template <typename... Args>
  static void
  debug(const char *location, const char *s, const Args &... args)
  {
    log(Log::DEBUG, location, s, args...);
  }

  template <typename... Args>
  static void
  error(const char *location, const char *s, const Args &... args)
  {
    log(Log::ERROR, location, s, args...);
  }

  template <typename... Args>
  static void
  check(
      const char *location, 
      bool result,
      const char *s,
      const Args &... args)
  {
    if (!result) {
      log(Log::ERROR, location, s, args...);
      throw AssertionError("assertion failed");
    }
  }

  template <typename... Args>
  static void
  fail(
      const char *location, 
      const char *s,
      const Args &... args) {
    check(location, false, s, args...);
  }

private:
  static const char *
  name(const Level &level)
  {
    return (const char *[]){
      "TRC", "DBG", "INF", "ERR"}[level];
  }

  template <typename... Args>
  static void
  log(
    const Level &level,
    const char *location,
    const char *s,
    const Args &... args)
  {
    if (level >= Log::level) {
      std::cerr << "[" << Log::name(level) << "] "
                << location << " " 
                << fmt::format(s, args...) << std::endl;
    }
  }
};
