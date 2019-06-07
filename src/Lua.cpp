#include <iostream>

#include "Lua.hpp"
#include "RayTracer.hpp"
#include "Cube.hpp"
#include "Mesh.hpp"
#include "UVMesh.hpp"
#include "Primitive.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"

#include "Log.hpp"
#include "GeometryNode.hpp"
#include "Node.hpp"

extern "C" {
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
}


#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

#include "Printglm.hpp"
#include "DebugMaterial.hpp"
#include "PhongMaterial.hpp"
#include "ReflectiveMaterial.hpp"
#include "Camera.hpp"

using namespace luabridge;
using namespace std;

namespace luabridge {

template <> struct Stack<const glm::dvec3 &> {
  static void
  push(lua_State *L, const glm::dvec3 &a)
  {
    assert(lua_checkstack(L, 3));
    lua_createtable(L, 3, 0);
    for (int i = 0; i < 3; i++) {
      lua_pushinteger(
        L,
        i + 1); // lua lists are 1-indexed :^)
      lua_pushnumber(L, a[i]);
      lua_settable(L, -3);
    }
  }

  static const glm::dvec3 
  get(lua_State *L, int index)
  {
    assert(lua_istable(L, index));
    double res[3];
    for (int i = 0; i < 3; i++) {
      lua_pushinteger(L, i + 1);
      lua_gettable(L, index);
      assert(lua_isnumber(L, -1));
      res[i] = lua_tonumber(L, -1);
    }
    return glm::dvec3(res[0], res[1], res[2]);
  }
};

}; // END namespace luabridge

void
echo()
{
  cout << "hello!" << endl;
}

void
initNamespace(lua_State *L)
{
  getGlobalNamespace(L)
    .beginNamespace("g")
    .addFunction("echo", echo)

    .beginClass<Camera>("Camera")
    .addConstructor<void (*)(
      const Point &,
      const Vector &,
      const Vector &,int, int, double)>()
    .endClass()

    .beginClass<Color>("Color")
    .addConstructor<void (*)(
      double c)>()
    .addConstructor<void (*)(
      double x, double y, double z)>()
    .endClass()

    .beginClass<Vector>("Vector")
    .addConstructor<void (*)(
      double x, double y, double z)>()
    .endClass()

    .beginClass<Point>("Point")
    .addConstructor<void (*)(
      double x, double y, double z)>()
    .endClass()

    .beginClass<Light>("Light")
    .addConstructor<void (*)(
      const Color &color, const Point &pos)>()
    .endClass()

    .beginClass<Primitive>("Primitive").endClass()

    .deriveClass<Cube, Primitive>("Cube")
    .addConstructor<void (*)()>()
    .endClass()

    .deriveClass<Sphere, Primitive>("Sphere")
    .addConstructor<void (*)()>()
    .endClass()

    .deriveClass<Mesh, Primitive>("Mesh")
    .addConstructor<void (*)(const std::string &name)>()
    .endClass()

    // .deriveClass<UVMesh, Mesh>("UVMesh")
    // .addConstructor<void (*)(const std::string &name)>()
    // .endClass()

    .beginClass<Material>("Material").endClass()

    .deriveClass<DebugMaterial, Material>("DebugMaterial")
    .addConstructor<void (*)()>()
    .endClass()

    // .deriveClass<ReflectiveMaterial, Material>(
    //   "ReflectiveMaterial")
    // .addConstructor<void (*)(
    //   const double &refractionIndex)>()
    // .endClass()

    .deriveClass<PhongMaterial, Material>("PhongMaterial")
    .addConstructor<void (*)(
      const Color &,
      const Color &,
      const double &)>()
    .endClass()

    .beginClass<Node>("Node")
    .addConstructor<void (*)(const std::string &)>()
    .addFunction("scale", &Node::scale)
    .addFunction("rotate", &Node::rotate)
    .addFunction("translate", &Node::translate)
    .addFunction("addChild", &Node::addChild)
    // .addFunction("intersect", &Node::intersect)
    .endClass()

    .deriveClass<GeometryNode, Node>("GeometryNode")
    .addConstructor<void (*)(
      const std::string &,
      const Primitive *const,
      const Material *)>()
    .endClass()

    .beginClass<RayTracer>("RayTracer")
    .addConstructor<void (*)(void)>()
    .addData(
      "renderReflection", &RayTracer::renderReflection)
    .addFunction("render", &RayTracer::render)
    .endClass()
    .endNamespace();
}

static int
traceback(lua_State *L)
{
  const char *LOCATION = "traceback";
  // @1 is the error message
  Log::error(LOCATION, "Error message: {}", lua_gettop(L));
  Log::error(LOCATION, "Error type: {}", lua_type(L, -1));

  if (!lua_isstring(L, 1))
    return 1;

  lua_pushglobaltable(L);
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }

  lua_getfield(L, -1, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }

  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }

  lua_pushvalue(L, 1);
  lua_call(L, 1, 1);
  return 1;
}

void
Lua::runScript(const char *fname)
{
  const char *LOCATION = "Lua::runScript";
  // Init the lua system
  lua_State *L = luaL_newstate();

  // Load in standard libraries
  luaL_openlibs(L);

  // Load all user defined methods
  initNamespace(L);

  // Add the traceback function
  lua_pushcfunction(L, traceback);

  int errorCode = luaL_loadfile(L, fname);
  if (errorCode) {
    Log::error(LOCATION,
        "Load file {} error: {}", fname, lua_tostring(L, -1));
    assert(0);
  }

  errorCode = lua_pcall(L, 0, 0, lua_gettop(L) - 1);
  if (errorCode) {
    Log::error(LOCATION, 
        "Lua error {}", lua_tostring(L, -1));
    assert(0);
  }
}
