#pragma once

#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;

ostream& operator<<(ostream& os, const glm::dvec3& d);

ostream& operator<<(ostream& os, const glm::dvec4& d);
