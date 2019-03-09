#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <cxxopts.hpp>

#include "node/GeometryNode.hpp"
#include "primitive/Sphere.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Lua.hpp"
#include "RuntimeConfig.hpp"

using namespace std;
using namespace glm;

int main(int argc, char *argv[]) {
  cxxopts::Options options("raytracer", "A poorly made ray tracer");
  options.add_options()
    ("d,debug", "Enable debugging")
    ("s,singlePixel", "Single pixel")
  ;
  auto result = options.parse(argc, argv);

  rc::init(new RuntimeConfig(
                             result["singlePixel"].as<bool>()
  ));
  Lua::runScript(argv[1]);
}
