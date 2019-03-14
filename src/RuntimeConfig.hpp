#pragma once
#include <memory>

struct RuntimeConfig {
  static std::unique_ptr<RuntimeConfig> rc;

  bool debug;
  bool singlePixel;
  RuntimeConfig(bool debug, bool singlePixel)
      : debug(debug), singlePixel(singlePixel)
  {
  }

  static void
  init(RuntimeConfig *rc)
  {
    RuntimeConfig::rc = std::unique_ptr<RuntimeConfig>(rc);
  }

  static RuntimeConfig &
  get()
  {
    return *RuntimeConfig::rc.get();
  }
};

typedef RuntimeConfig rc;
