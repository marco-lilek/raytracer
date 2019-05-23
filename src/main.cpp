#include <cxxopts.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <string>

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
  }

  RuntimeConfig::init(new RuntimeConfig(
    debug, window));
  Lua::runScript(argv[1]);
}
