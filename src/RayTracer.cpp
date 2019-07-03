#include "RayTracer.hpp"
#include "Scene.hpp"
#include "Image.hpp"
#include "Log.hpp"
#include "Camera.hpp"
#include "RuntimeConfig.hpp"

using namespace std;
using namespace Glm;

void
RayTracer::render(
  const Node *rootNode,
  const Camera &camera,
  const std::vector<const Light *> &lights,
  const std::string &fname)
{
  const char * LOCATION = "RayTracer::render";

  Log::check(LOCATION, rootNode != NULL, "rootNode is null");
  Log::info(LOCATION, "camera {}", camera);
  Log::info(LOCATION, "fname {}", fname);

  for (auto lightIt = lights.begin();
       lightIt != lights.end();
       lightIt++) {
    const Light *l = *lightIt;
    Log::info(LOCATION, "light {}: {}", 
        lightIt - lights.begin(), 
        *l);
  }

  // Initialize the image
  Image img(camera.width, camera.height);

  // Initialize the scene
  const Scene scene(rootNode, lights);

  Log::info(LOCATION, "scene {}", scene);

  // Initialize the camera
  int distanceFromEyeToScreen = 1;

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
      try {
        Log::trace(LOCATION, "firing ray to i {} j {}", i, j);
        const Ray rayFromEyeToScreen = camera.getRayFromEyeToScreen(i, j);
        Log::trace(LOCATION, "rayFromEyeToScreen {}", rayFromEyeToScreen);
        const Vec3 pixelColor = scene.getColor(rayFromEyeToScreen);
        Log::trace(LOCATION, "pixelColor {}", pixelColor);
        img.drawPixel(i, j, pixelColor);
      } catch (const AssertionError &e) {
        Log::error(LOCATION, "i {} j {}", i, j);
        if (RuntimeConfig::get().drawDeadPixels) {
          img.drawPixel(i, j, Vec3(0));
        } else {
          throw;
        }
      }
    }
  }

  // Write the drawn image out to fname
  Log::info(LOCATION, "rendering to: {}", fname);
  img.render(fname);
}
