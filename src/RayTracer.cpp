#include "RayTracer.hpp"
#include "Scene.hpp"
#include "Image.hpp"
#include "Log.hpp"
#include "RayGun.hpp"
#include "Camera.hpp"
#include "RuntimeConfig.hpp"

using namespace std;

void
RayTracer::render(
  const Node *rootNode,
  const std::vector<const Light *> &lights,
  const std::string &fname,
  const int width,
  const int height)
{
  const char * LOCATION = "RayTracer::render";
  // TODO: assert rootnode not null

  Log::info(LOCATION, 
      "rootNode: {} lights: {} fname: {} width: {} height: {}",
      *rootNode, lights.size(), fname, width, height);

  for (auto lightIt = lights.begin();
       lightIt != lights.end();
       lightIt++) {
    const Light *l = *lightIt;
    Log::info(LOCATION, "light {}: {}", 
        lightIt - lights.begin(), 
        *l);
  }

  // Initialize the image we're rendering to
  Image img(width, height);
  
  // Initialize the scene
  const Scene scene(rootNode, lights);

  // Initialize the camera
  int distanceFromEyeToScreen = 1;
  const Camera camera(Point(0,0,0) /* eye */, 
      Vector(0,1,0) /* up */,
      Vector(0,0,1) /* towards */,
      width,
      height);

  int startX = 0;
  int startY = 0;
  int endX = img.width;
  int endY = img.height;

  if (RuntimeConfig::get().singlePixel) {
    Log::info(LOCATION, "shooting single pixel");
    startX = img.width / 2;
    startY = img.height / 2;
    endX = img.width / 2 + 1;
    endY = img.height / 2 + 1;
  }

  for (int i = startX; i < endX; i++) {
    for (int j = startY; j < endY; j++) {
      const Ray rayFromEyeToScreen = camera.getRayFromEyeToScreen(i, j);
      const Color pixelColor = scene.getColor(rayFromEyeToScreen);
      img.drawPixel(i, j, pixelColor);
    }
  }

  // Write the drawn image out to fname
  Log::info(LOCATION, "rendering to: {}", fname);
  img.render(fname);
}
