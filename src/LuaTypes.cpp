#include "LuaTypes.hpp"

namespace luabridge {

void
Stack<const Glm::Vec3&>::push(lua_State *L, const Glm::Vec3 &a)
{
  assert(lua_checkstack(L, 3));
  lua_createtable(L, 0, 3);
  for (int i = 0; i < 3; i++) {
    lua_pushinteger(
      L,
      i + 1); // lua lists are 1-indexed :^)
    lua_pushnumber(L, a[i]);
    lua_settable(L, -3);
  }
}

const Glm::Vec3 
Stack<const Glm::Vec3&>::get(lua_State *L, int index)
{
  assert(lua_istable(L, index));
  double res[3];
  for (int i = 0; i < 3; i++) {
    lua_pushinteger(L, i + 1);
    lua_gettable(L, index);
    assert(lua_isnumber(L, -1));
    res[i] = lua_tonumber(L, -1);
  }
  return Glm::Vec3(res[0], res[1], res[2]);
}

}; // END namespace luabridge
