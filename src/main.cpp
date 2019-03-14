#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <cxxopts.hpp>

#include "node/GeometryNode.hpp"
#include "primitive/Sphere.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Lua.hpp"
#include "Debug.hpp"

using namespace std;
using namespace glm;

int main(int argc, char *argv[]) {
  cxxopts::Options options("raytracer", "A poorly made ray tracer");
  options.add_options()
    ("d,debug", "Enable debugging")
    ("s,singlePixel", "Single pixel")
  ;
  auto result = options.parse(argc, argv);

  //spdlog::set_pattern("[thread %t][%l][%@ %!] %v");
  bool debug = result["debug"].as<bool>();
  if (debug) {
    Log::level = Log::DEBUG;
  }
  

  rc::init(new RuntimeConfig(debug,
                             result["singlePixel"].as<bool>()
  ));
  Lua::runScript(argv[1]);
}
