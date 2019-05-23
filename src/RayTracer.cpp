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
  const Camera &camera,
  const std::vector<const Light *> &lights,
  const std::string &fname,
  const int width,
  const int height)
{
  const char * LOCATION = "RayTracer::render";
  // TODO: assert rootnode not null

  Log::info(LOCATION, 
      "rootNode {} camera {} lights.size() {} fname {} width {} height {}",
      *rootNode, camera, lights.size(), fname, width, height);

  for (auto lightIt = lights.begin();
       lightIt != lights.end();
       lightIt++) {
    const Light *l = *lightIt;
    Log::info(LOCATION, "light {}: {}", 
        lightIt - lights.begin(), 
        *l);
  }

  // Initialize the image
  Image img(width, height);

  // Initialize the scene
  const Scene scene(rootNode, lights);

  // TODO trace dump the img and the scene

  // Initialize the camera
  int distanceFromEyeToScreen = 1;

  // TODO pass in the single pixel to be shot
  int startX = 0;
  int startY = 0;
  int endX = img.width;
  int endY = img.height;

  {
    const ViewWindow &viewWindow = RuntimeConfig::get().viewWindow;
    if (!viewWindow.isEmpty()) {
      Log::info(LOCATION, "drawing viewWindow {}", viewWindow);
      startX =  viewWindow.x1;
      endX =    viewWindow.x2;
      startY =  viewWindow.y1;
      endY =    viewWindow.y2;
    }
  }

  for (int i = startX; i < endX; i++) {
    for (int j = startY; j < endY; j++) {
      const double windowOffsetX = (double)i / img.width;
      const double windowOffsetY = (double)j / img.height;

      const Ray rayFromEyeToScreen = camera.getRayFromEyeToScreen(
          windowOffsetX, windowOffsetY);
      const Color pixelColor = scene.getColor(rayFromEyeToScreen);
      img.drawPixel(i, j, pixelColor);
    }
  }

  // Write the drawn image out to fname
  Log::info(LOCATION, "rendering to: {}", fname);
  img.render(fname);
}
