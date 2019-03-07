#include <iostream>

#include "Lua.hpp"
#include "RayTracer.hpp"

#include "primitive/Primitive.hpp"
#include "primitive/Sphere.hpp"
#include "primitive/Cube.hpp"

#include "node/GeometryNode.hpp"
#include "node/Node.hpp"

extern "C" {
# include <lua5.3/lua.h>
# include <lua5.3/lauxlib.h>
# include <lua5.3/lualib.h>
}

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

#include "material/PhongMaterial.hpp"
#include "material/DebugMaterial.hpp"
#include "node/SphereNode.hpp"
#include "PrintGlm.hpp"

using namespace luabridge;
using namespace std;

namespace luabridge {

    template <>
    struct Stack <const glm::dvec3 &>
    {
        static void push (lua_State* L, const glm::dvec3 &a)
        {
            assert(lua_checkstack(L, 3));
            lua_createtable(L, 3, 0);
            for (int i = 0; i < 3; i++) {
              lua_pushinteger(L, i+1); // lua lists are 1-indexed :^)
              lua_pushnumber(L, a[i]);
              lua_settable(L, -3);
            }
        }

      static const glm::dvec3 get (lua_State* L, int index)
        {
          assert(lua_istable(L, index));
          glm::dvec3 res;
          for (int i = 0; i < 3; i++) {
            lua_pushinteger(L, i+1);
            lua_gettable(L, index);
            assert(lua_isnumber(L, -1));
            res[i] = lua_tonumber(L, -1);
          }
          cerr << res << endl;
          return res;
        }
    };

};
void echo() {
  cout << "hello!" << endl;
}
 
void initNamespace(lua_State *L) {
  getGlobalNamespace(L)
    .beginNamespace("g")
      .addFunction("echo", echo)

      .beginClass<Light>("Light")
      .addConstructor<void (*) (
        const glm::dvec3 &color,
        const glm::dvec3 &pos
      )>()
      .endClass()

      .beginClass<Primitive>("Primitive")
        .addFunction("intersect", &Primitive::intersect)
      .endClass()

      .beginClass<Material>("Material")
        .addFunction("intersect", &Material::intersect)
      .endClass()

      .beginClass<DebugMaterial>("DebugMaterial")
        .addFunction("intersect", &DebugMaterial::intersect)
      .endClass()

      .deriveClass<PhongMaterial, Material>("PhongMaterial")
        .addConstructor<void (*)(
            const glm::dvec3 &,
            const glm::dvec3 &,
            const double &
                                 )>()
      .endClass()

      .beginClass<Node>("Node")
        .addConstructor<void (*) (const std::string&)>()
        .addFunction("scale", &Node::scale)
        .addFunction("rotate", &Node::rotate)
        .addFunction("translate", &Node::translate)
        .addFunction("addChild", &Node::addChild)
        .addFunction("intersect", &Node::intersect)
      .endClass()

      .deriveClass<GeometryNode, Node>("GeometryNode")
        .addConstructor<void (*) (
                                  const std::string&,
                                  const Primitive * const,
                                  const Material *
                                  )>()
      .endClass()

      .deriveClass<SphereNode, Node>("SphereNode")
        .addConstructor<void (*) (
                                  const std::string&,
                                  const Material *
                                  )>()
      .endClass()

      .beginClass<RayTracer>("RayTracer")
        .addConstructor<void (*) (void)>()
        .addData("renderReflection", &RayTracer::renderReflection)
        .addFunction("render", &RayTracer::render)
      .endClass()
    .endNamespace();
}

static int traceback(lua_State *L) { 
  // @1 is the error message
  if (!lua_isstring(L,1)) return 1;

  lua_pushglobaltable(L);
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2); // pop gt and traceback
    return 1;
  }
  lua_pushvalue(L, 1);
  lua_pushinteger(L, 2);
  lua_call(L, 2, 1);
  return 1;
}

void Lua::runScript(const char * fname) {
  lua_State* L = luaL_newstate();

  luaL_openlibs(L);
  initNamespace(L);

  luaL_dofile(L, fname);
  lua_pushcfunction(L, traceback);
  lua_pcall(L, 0, 0, -1);
}
