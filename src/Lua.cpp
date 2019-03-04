#include <iostream>

#include "Lua.hpp"
#include "RayTracer.hpp"

#include "primitive/Primitive.hpp"
#include "primitive/Sphere.hpp"

#include "node/GeometryNode.hpp"
#include "node/Node.hpp"


extern "C" {
# include <lua5.3/lua.h>
# include <lua5.3/lauxlib.h>
# include <lua5.3/lualib.h>
}

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

using namespace luabridge;
using namespace std;

void echo() {
  cout << "hello!" << endl;
}
 
void initNamespace(lua_State *L) {
  getGlobalNamespace(L)
    .beginNamespace("g")
      .addFunction("echo", echo)

      .beginClass<Primitive>("Primitive")
        .addFunction("intersect", &Primitive::intersect)
      .endClass()

      .deriveClass<Sphere, Primitive>("Sphere")
        .addConstructor<void (*) (const double &radius)>()
      .endClass()

      .beginClass<Material>("Material")
        .addConstructor<void (*)(
            const std::vector<double> &kd,
            const std::vector<double> &ks,
            const double &shininess,
            const double &reflectiveness)>()
      .endClass()

      .beginClass<Node>("Node")
        .addConstructor<void (*) (const std::string&)>()
        .addFunction("scale", &Node::scaleList)
        .addFunction("rotate", &Node::rotate)
        .addFunction("translate", &Node::translateList)
        .addFunction("addChild", &Node::addChild)
        .addFunction("intersect", &Node::intersect)
      .endClass()

      .deriveClass<GeometryNode, Node>("GeometryNode")
        .addConstructor<void (*) (const std::string&, const Primitive * const, const Material &)>()
      .endClass()

      .beginClass<RayTracer>("RayTracer")
        .addConstructor<void (*) (void)>()
        .addData("renderReflection", &RayTracer::renderReflection)
        .addFunction("render", &RayTracer::render)
      .endClass()
    .endNamespace();
}

static int traceBack(lua_State *L) {
  lua_getglobal(L, "debug");
  if (!lua_istable(L, -1)) {
    
  }
}

void Lua::runScript(const char * fname) {
  lua_State* L = luaL_newstate();

  luaL_openlibs(L);
  initNamespace(L);

  luaL_dofile(L, fname);
  lua_pcall(L, 0, 0, 0);
}
