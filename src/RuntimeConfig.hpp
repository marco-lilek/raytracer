#pragma once
#include <memory>
#include "ViewWindow.hpp"

struct RuntimeConfig {
  bool debug;
  ViewWindow viewWindow;
  RuntimeConfig(bool debug, const ViewWindow &window)
      : debug(debug), viewWindow(window)
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

private:
  static std::unique_ptr<RuntimeConfig> rc;

};

