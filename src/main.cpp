#include <iostream>
#include <cxxopts.hpp>
#include "spdlog/spdlog.h"
#include "lua_bridge.hpp"
#include "ViewWindow.hpp"
#include "RuntimeConfig.hpp"

int main(int argc, char *argv[]) {
  cxxopts::Options options(
          "raytracer", "A poorly made ray tracer");
  options.add_options()
          ("d,debug", "Enable debugging")
          ("t,trace", "Enable trace")
          ("ddp", "Draw dead pixels")
          ("sp", "Single pixel x,y", cxxopts::value<std::string>())
          ("window", "View window x1,x2,y1,y2", cxxopts::value<std::string>());
  auto result = options.parse(argc, argv);

  // spdlog::set_pattern("[thread %t][%l][%@ %!] %v");
  bool debug = result["debug"].as<bool>();
  bool trace = result["trace"].as<bool>();
  if (debug) {
    spdlog::set_level(spdlog::level::debug);
  }
  if (trace) {
    spdlog::set_level(spdlog::level::trace);
  }

  ViewWindow *window = nullptr;
  if (result.count("window") == 1) {
    window = ViewWindow::fromWindow(result["window"].as<std::string>());
  } else if (result.count("sp") == 1) {
    window = ViewWindow::fromPoint(
            result["sp"].as<std::string>());
  }

  RuntimeConfig::init(new RuntimeConfig());
  RuntimeConfig &rc = RuntimeConfig::get();
  rc.drawDeadPixels = result["ddp"].as<bool>();
  rc.viewWindow = window;
  run_lua(argv[1]);
  return 0;
}