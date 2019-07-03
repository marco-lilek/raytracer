#include "TextureLoader.hpp"
#include "Log.hpp"
#include "Color.hpp"

#include <lodepng/lodepng.h>

using namespace Glm;

const Texture *
TextureLoader::loadTexture(const std::string &name) {
  const char* TRACE_HEADER = "TextureLoader::loadTexture";
  
  // TODO don't hard code the path
  std::string filename = "../assets/" + name;

  std::vector<unsigned char> image; //the raw pixels
  unsigned width, height;

  unsigned error = lodepng::decode(image, width, height, filename);

  Log::check(TRACE_HEADER, !error, "error loading {}: {}", filename, lodepng_error_text(error));

  Log::info(TRACE_HEADER, "loaded {} width {} height {}", filename, width, height);

  int NUM_BYTES_PER_PIXEL = 4;
  int numPixels = width * height;

  Texture *texture = new Texture(width, height);

  double x,y,z;
  for (int i = 0; i < numPixels; i++) {
    int sidx = i*NUM_BYTES_PER_PIXEL;
    x = Color::decode(image[sidx+0]);
    y = Color::decode(image[sidx+1]);
    z = Color::decode(image[sidx+2]); 
    Vec3 data(x,y,z);
    texture->data[i] = data;
    //Log::trace("sdf", "i {} data {}", i, data);

    //texture->data[i+3] = 
  }

  return texture;
}
