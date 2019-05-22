#include "DebugMaterial.hpp"


Color DebugMaterial::getColor(
    const GeometryIntersection::ShooterPos &shooterPos) const {
  switch (shooterPos) {
    case GeometryIntersection::Towards:
      return Color(1); // White
    break;
    case GeometryIntersection::Inside:
      return Color(1,0,0); // Red
    break;
    case GeometryIntersection::Past:
    case GeometryIntersection::Miss:
    default:
      return Color(0); // Black
    break;
  };
}
