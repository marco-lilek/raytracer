#include <iostream>

#include "Lua.hpp"
#include "RayTracer.hpp"
#include "Cube.hpp"
#include "Mesh.hpp"
#include "UVMesh.hpp"
#include "Geometry.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"

#include "Log.hpp"
#include "GeometryNode.hpp"
#include "PrimitiveNode.hpp"
#include "Node.hpp"

#include "DebugMaterial.hpp"
#include "PhongMaterial.hpp"
#include "ReflectiveMaterial.hpp"
#include "TextureMaterial.hpp"
#include "Camera.hpp"

#include "LuaTypes.hpp"

using namespace luabridge;
using namespace std;

void
echo()
{
  cout << "hello!" << endl;
}

// Note to self:
// Lua is very picky about its arguments---if you see errors like
//
// terminate called after throwing an instance of 'std::logic_error'
// what():  The class is not registered in LuaBridge
// Aborted (core dumped)
//
// Make sure the arguments (type + const + ref vs pointer) are correct

Mesh* create_uvmesh(const string&name) {
  // TODO: Use the meshloader
  UVMesh *mesh = new UVMesh(name);
  MeshLoader loader(name);
  loader.loadMesh(mesh);
  return mesh;
}

Mesh* create_mesh(const string&name) {
  Mesh *mesh = new Mesh(name);
  MeshLoader loader(name);
  loader.loadMesh(mesh);
  return mesh;
}

Material *create_texture(const string&name) {
  return new TextureMaterial(name);
}

Material *create_phong_material(const Glm::Vec3 &kd,
    const Glm::Vec3 &ks,
    const double &shininess) {
  return new PhongMaterial(kd, ks, shininess);
}

Node *create_node(const string&name) {
  return new Node(name);
}

Node *create_geometry_node(
    const string&name,
    const Geometry *const p,
    const Material *m) {
  return new GeometryNode(name, p, m);
}

const Light *create_light(
    const Glm::Vec3 &color,
    const Glm::Vec3 &pos) {
  return new Light(color, pos);
}

Camera *create_camera(
      const Glm::Vec3 &eye,
      const Glm::Vec3 &up,
      const Glm::Vec3 &towards,
      int width,
      int height,
      double fov) {
  return new Camera(eye, up, towards, width, height, fov);
}

void render(
    const Node *root,
    const Camera *camera,
    const vector<const Light *> &lights,
    const string&fname) {
  RayTracer r;
  r.render(root, *camera, lights, fname);
}

void
initNamespace(lua_State *L)
{
  getGlobalNamespace(L)
    .beginNamespace("g")
    .addFunction("echo", echo)
    .addFunction("uvmesh", create_uvmesh)
    .addFunction("mesh", create_mesh)
    .addFunction("texture", create_texture)
    .addFunction("phong_material", create_phong_material)

    .addFunction("node", create_node)
    .addFunction("geometry_node", create_geometry_node)

    .addFunction("light", create_light)
    .addFunction("camera", create_camera)
    .addFunction("render", render)

    .beginClass<Camera>("Camera").endClass()
    .beginClass<Light>("Light").endClass()

    .beginClass<Geometry>("Geometry").endClass()
    .deriveClass<Mesh, Geometry>("Mesh").endClass()

    .beginClass<Material>("Material").endClass()

    .beginClass<Node>("Node")
    .addFunction("scale", &Node::scale)
    .addFunction("rotate", &Node::rotate)
    .addFunction("translate", &Node::translate)
    .addFunction("addChild", &Node::addChild)
    // .addFunction("intersect", &Node::intersect)
    .endClass()

    .beginClass<RayTracer>("RayTracer").endClass()
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
