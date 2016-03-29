#include "bbox.h"

#include "GL/glew.h"

#include <algorithm>
#include <iostream>

namespace CGL {

void BBox::intersect_planes(const Ray& r, int axis, double& tmin, double& tmax) const{
    double p1 = min[axis];
    double p2 = max[axis];
    double o = r.o[axis];
    double d = r.d[axis];
    if (d == 0.f) {
      if ((p1<=o) && (o<=p2)) {
        tmin = -INF_D;
        tmax = INF_D;
      } else {
        tmin = INF_D;
        tmax = -INF_D;
      }
    } else {
      double t1 = (p1-o)/d;
      double t2 = (p2-o)/d;
      tmin = std::min(t1,t2);
      tmax = std::max(t1,t2);
    }
}
bool BBox::intersect(const Ray& r, double& t0, double& t1) const {
  // TODO Part 2, task 2:
  // Implement ray - bounding box intersection test
  // If the ray intersected the bounding box within the range given by
  // t0, t1, update t0 and t1 with the new intersection times.
  //std::cout << "testing bbox: " << std::endl;
  double tminx, tminy, tminz;
  double tmaxx, tmaxy, tmaxz;
  intersect_planes(r, 0, tminx, tmaxx);
  intersect_planes(r, 1, tminy, tmaxy);
  intersect_planes(r, 2, tminz, tmaxz);
  double tmin = std::max(std::max(tminx, tminy), tminz);
  double tmax = std::min(std::min(tmaxx, tmaxy), tmaxz);
  //std::cout << "tmin:" << tmin << "; tmax: " << tmax << std::endl;
  //std::cout << "t0:" << t0 << "; t1: " << t1 << std::endl;
  if ((tmin <= tmax)&&(t0<=tmin)&&(t1>=tmax)) {
      //std::cout << "tmin:" << t0 << "; tmax: " << t1 << std::endl;
      t0 = tmin;
      t1 = tmax;
      //std::cout << "true" << std::endl;
      return true;
  }
  //std::cout << "false" << std::endl;
  return false;
}

void BBox::draw(Color c) const {

  glColor4f(c.r, c.g, c.b, c.a);

	// top
	glBegin(GL_LINE_STRIP);
	glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(max.x, max.y, max.z);
	glEnd();

	// bottom
	glBegin(GL_LINE_STRIP);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, min.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, min.y, min.z);
	glEnd();

	// side
	glBegin(GL_LINES);
	glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, min.y, max.z);
	glVertex3d(max.x, max.y, min.z);
  glVertex3d(max.x, min.y, min.z);
	glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, min.y, min.z);
	glVertex3d(min.x, max.y, max.z);
  glVertex3d(min.x, min.y, max.z);
	glEnd();

}

std::ostream& operator<<(std::ostream& os, const BBox& b) {
  return os << "BBOX(" << b.min << ", " << b.max << ")";
}

} // namespace CGL
