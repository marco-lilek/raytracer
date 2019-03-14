#include "primitive/Mesh.hpp"
#include "ObjLoader.hpp"
#include <iostream>

using namespace std;

Mesh::Mesh(const std::string &name) : Primitive()
{
  // TODO: better model loading paths
  importModel("../src/models/" + name,
              positions, normals, uvCoords, tangents);
}

bool Mesh::intersect(const Ray &r,
                        float &t,
                        glm::dvec4 &normal) const
{
  bool intersects = false;

  glm::vec3 ev(r.from);
  glm::vec3 dv(r.v);
  double a,b,c,d,e,f,g,h,i,j,k,l;
  for (size_t fidx = 0; fidx < positions.size(); fidx += 3) { // taken from textbook
    glm::vec3 va(positions[fidx]);
    glm::vec3 vb(positions[fidx+1]);
    glm::vec3 vc(positions[fidx+2]);

    a = va.x-vb.x; b = va.y-vb.y; c = va.z-vb.z;
    d = va.x-vc.x; e = va.y-vc.y; f = va.z-vc.z;
    g = dv.x; h = dv.y; i = dv.z;

    j = va.x - ev.x; k = va.y - ev.y; l = va.z - ev.z;

    double M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);

    double tp = - (f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c)) / M;

    cerr << tp << endl;
    if (tp < 0) continue; // Doesnt intersect this plane
    if (intersects && tp > t) continue; // We've already intersected at a nearer point

    double gam = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c)) / M;
    if (gam < 0 || gam > 1) continue;

    double bet = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g)) / M;

  //  cerr << fidx << " " << bet << " " << gam << endl;
    if (bet < 0 || (bet+gam != 1.0 && bet + gam > 1)) continue;

    t = tp;

    normal = glm::vec4(glm::cross(vb - va, vc - vb), 0);
  //  cerr << glm::to_string(N) << " " << tp<< endl;
    intersects = true;
  }

  return intersects;
}
