#pragma once

#include "Glm.hpp"

extern "C" {
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
}

#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

namespace luabridge {

template <> struct Stack<const Glm::Vec3&> {
  static void
  push(lua_State *L, const Glm::Vec3&a);

  static const Glm::Vec3 
  get(lua_State *L, int index);
};

}; // END namespace luabridge

