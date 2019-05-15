#include <cxxopts.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "Debug.hpp"
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
  cxxopts::Options options(
    "raytracer", "A poorly made ray tracer");
  options.add_options()
  ("d,debug", "Enable debugging")
  ("t,trace", "Enable trace")
  ("s,singlePixel", "Single pixel");
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

  RuntimeConfig::init(new RuntimeConfig(
    debug, result["singlePixel"].as<bool>()));
  Lua::runScript(argv[1]);
}
