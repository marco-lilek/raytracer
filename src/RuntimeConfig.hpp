#pragma once
#include <memory>
#include "ViewWindow.hpp"

struct RuntimeConfig : public Object {
  bool drawDeadPixels;
  ViewWindow viewWindow;
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

  virtual const char * type() const {
    return "RuntimeConfig";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "drawDeadPixels " << drawDeadPixels << " viewWindow " << viewWindow;
  }

private:
  static std::unique_ptr<RuntimeConfig> rc;

};

