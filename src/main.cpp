#include <cxxopts.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>

#include "ViewWindow.hpp"
#include "RuntimeConfig.hpp"
#include "Image.hpp"
#include "Light.hpp"
#include "Lua.hpp"
#include "Scene.hpp"
#include "GeometryNode.hpp"
#include "Sphere.hpp"

using namespace std;
using namespace glm;

int
main(int argc, char *argv[])
{
  const char * TRACE_HEADER = "main";
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
    Log::level = Log::DEBUG;
  }
  if (trace) {
    Log::level = Log::TRACE;
  }

  ViewWindow window;
  if (result.count("window") == 1) {
    window = result["window"].as<std::string>();
  } else if (result.count("sp") == 1) {
    window = ViewWindow::fromPoint(
        result["sp"].as<std::string>());
  }

  RuntimeConfig::init(new RuntimeConfig());
  RuntimeConfig &rc = RuntimeConfig::get();
  rc.drawDeadPixels = result["ddp"].as<bool>();
  rc.viewWindow = window;
  Log::debug(TRACE_HEADER, "runtimeConfig {}", rc);
  Lua::runScript(argv[1]);
}
