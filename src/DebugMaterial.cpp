#include "DebugMaterial.hpp"

using namespace Glm;

Vec3 DebugMaterial::getColor(
    const GeometryIntersection::ShooterPos &shooterPos) const {
  switch (shooterPos) {
    case GeometryIntersection::Towards:
      return Vec3(1); // White
    break;
    case GeometryIntersection::Inside:
      return Vec3(1,0,0); // Red
    break;
    case GeometryIntersection::Past:
    case GeometryIntersection::Miss:
    default:
      return Vec3(0); // Black
    break;
  };
}
