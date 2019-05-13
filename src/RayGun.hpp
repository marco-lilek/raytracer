#include "Scene.hpp"
#include "Intersection.hpp"
#include "LightRay.hpp"

class RayGun {
public:
  RayGun(const Scene &scene);

  const Intersection
  fireRay(const LightRay &r) const;
private:
};
