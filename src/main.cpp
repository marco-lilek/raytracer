#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "node/GeometryNode.hpp"
#include "primitive/Sphere.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Lua.hpp"

using namespace std;
using namespace glm;

int main(int argc, char *argv[]) {
  Lua::runScript(argv[1]);
}
