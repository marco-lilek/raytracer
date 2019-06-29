#include "TextureLoader.hpp"
#include "Log.hpp"
#include "Color.hpp"

#include <lodepng/lodepng.h>

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

  for (int i = 0; i < numPixels; i += NUM_BYTES_PER_PIXEL) {
    double x,y,z;
    x = Color::decode(image[i+0]);
    y = Color::decode(image[i+1]);
    z = Color::decode(image[i+2]); 
    texture->data[i] = glm::dvec3(x,y,z);

    //texture->data[i+3] = 
  }
}
