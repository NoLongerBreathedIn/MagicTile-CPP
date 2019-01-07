#include "vector3d.hpp"
#include "../math/utils.hpp"
#include <boost/functional/hash.hpp>
std::ostream &operator<<(std::ostream &os, const vector3d &v);

vector3d operator*(const vector3d &v, double d);
vector3d operator*(double d, const vector3d &v);
vector3d operator/(const vector3d &v, double d);
vector3d &operator*=(vector3d &v, double d);
vector3d &operator/=(vector3d &v, double d);
vector3d vector3d::load(const char *s);
vector3d operator+(const vector3d &v, const vector3d &w);
vector3d operator-(const vector3d &v, const vector3d &w);
vector3d &operator+=(vector3d &v, const vector3d &w);
vector3d &operator-=(vector3d &v, const vector3d &w);
std::size_t hash_value(const vector3d &v);
double vector3d::dot(const vector3d &v);
bool vector3d::normalize(double scale) {
  double mag = abs();
  if(eqtol(mag))
    return(false);
  *this *= scale / mag;
  return(true);
}
