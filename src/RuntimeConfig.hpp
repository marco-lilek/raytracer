#pragma once
#include <memory>
#include "ViewWindow.hpp"

struct RuntimeConfig {
  bool drawDeadPixels;
  ViewWindow *viewWindow;
  RuntimeConfig()
  { }

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
private:
  static std::unique_ptr<RuntimeConfig> rc;
};

