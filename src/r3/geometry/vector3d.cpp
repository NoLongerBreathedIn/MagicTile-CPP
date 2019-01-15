#include "vector3d.hpp"
#include "../math/utils.hpp"
#include <boost/functional/hash.hpp>
#include <cstdio>

const vector3d DNE_VEC(NAN, NAN, NAN, NAN);
std::ostream &operator<<(std::ostream &os, const vector3d &v) {
	return(os << v.x << ',' << v.y << ',' << v.z << ',' << v.w);
}

std::size_t hash_value(const vector3d &v) {
  size_t s = boost::hash<int>()(v.x);
  boost::hash_combine(s, v.y);
  boost::hash_combine(s, v.z);
  boost::hash_combine(s, v.w);
  return(s);
}
double vector3d::dot(const vector3d &v) const {
	return(x * v.x + y * v.y + z * v.z + w * v.w);
}
bool vector3d::normalize(double scale) {
  double mag = abs();
  if(eqtol(mag))
    return(false);
  *this *= scale / mag;
  return(true);
}

vector3d vector3d::load(const char *c) {
  vector3d v;
  sscanf(c, "%lf,%lf,%lf,%lf", &v.x, &v.y, &v.z, &v.w);
  return(v);
}
  
void vector3d::rotateXY(double angle) {
  double xx = x, yy = y;
  double s = std::sin(angle), c = std::cos(angle);
  x = xx * c - yy * s;
  y = xx * s + yy * c;
}
void vector3d::rotateAxis(vector3d axis, double angle) {
  axis.w = 0;
  axis.normalize();
  double as[] = {axis.x, axis.y, axis.z};
  double c = std::cos(angle);
  double s = std::sin(angle);
  double vs = 1 - c;
  double angs[] = {c, s, -s};
  double cs[] = {x, y, z};
  double couts[] = {0,0,0};
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      couts[i] += cs[j] * (vs * as[i] * as[j] + angs[(i + 3 - j) % 3] *
			   (i == j? 1 : as[3 - i - j]));
}
double vector3d::angleTo(const vector3d &v) const {
  double mm = std::sqrt(magSquared() * v.magSquared());
  if(eqtol(mm))
    return(0);
  double val = dot(v) / mm;
  if(val > 1)
    val = 1;
  if(val < -1)
    val = -1;
  return(std::acos(val));
}
vector3d vector3d::cross(const vector3d &v) const {
  vector3d c(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  return(c);
}
vector3d vector3d::perpendicular() const {
  if(x == 0 && y == 0 && z == 0)
    return(*this);
  const static vector3d zax(0,0,1);
  const static vector3d xax(1,0,0);
  vector3d perp = cross(zax);
  if(perp.x == 0 && perp.y == 0)
    perp = cross(xax);
  perp.normalize();
  return(perp);
}

const static double minD = .0001;
vector3d vector3d::proj3dsafe(double cameraDist) const {
  double den = cameraDist - w;
  if(letol(den, 0))
    den = minD;
  vector3d r = *this * (cameraDist / den);
  r.w = 0;
  return(r);
}

vector3d vector3d::centralProject(double cameraDist) const {
  double den = cameraDist - z;
  if(letol(den, 0))
     den = 0;
  vector3d r = *this * (cameraDist / den);
  r.w = r.z = 0;
  return(r);
}
