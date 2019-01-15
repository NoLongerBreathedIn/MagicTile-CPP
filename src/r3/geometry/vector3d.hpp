#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <complex>
#include <ostream>
#include <cmath>
#include <cstddef>

class vector3d {
public:
  inline vector3d(double x = 0, double y = 0, double z = 0, double w = 0) :
    x(x), y(y), z(z), w(w) {}
  double x, y, z, w;
  static vector3d load(const char *s);
  inline operator std::complex<double>() const {
    return std::complex<double>(x, y);
  }
  inline double &operator[](int ix) {
    switch(ix) {
    case 0:
      return(x);
    case 1:
      return(y);
    case 2:
      return(z);
    default:
      return(w);
    }
  }
  inline double operator[](int ix) const {
    switch(ix) {
    case 0:
      return(x);
    case 1:
      return(y);
    case 2:
      return(z);
    default:
      return(w);
    }
  }
  inline bool dne() const {
    return(std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w));
  }
  inline void empty() {
    x = y = z = w = 0;
  }
  bool normalize(double scale = 1);
  inline double abs() const {
    return(std::sqrt(magSquared()));
  }
  inline double magSquared() const {
    return(this->dot(*this));
  }
  double dist(const vector3d &v) const;
  double dot(const vector3d &v) const;
  inline void rotate90() {
    double t = x;
    x = -y;
    y = t;
  }
  void rotateXY(double angle);
  void rotateAxis(vector3d axis, double angle);
  double angleTo(const vector3d &v) const;
  vector3d cross(const vector3d &v) const;
  vector3d perpendicular() const;
  vector3d proj3dsafe(double cameraDist) const;
  vector3d centralProject(double cameraDist) const;
  inline bool infinite() const {
    return(!(std::isfinite(x) && std::isfinite(y) &&
	     std::isfinite(z) && std::isfinite(w)));
  }
};

extern const vector3d DNE_VEC;

inline bool operator==(const vector3d &a, const vector3d &b) {
  return(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
inline bool operator!=(const vector3d &a, const vector3d &b) {
  return(!(a == b));
}

extern std::size_t hash_value(const vector3d &v);

extern std::ostream &operator<<(std::ostream &os, const vector3d &v);

inline vector3d &operator*=(vector3d &v, double d) {
	v.x *= d;
	v.y *= d;
	v.z *= d;
	v.w *= d;
	return(v);
}
inline vector3d &operator/=(vector3d &v, double d) {
	v.x /= d;
	v.y /= d;
	v.z /= d;
	v.w /= d;
	return(v);
}
inline vector3d operator*(const vector3d &v, double d) {
	vector3d w = v;
	return(w *= d);
}
inline vector3d operator*(double d, const vector3d &v) {
	vector3d w = v;
	return(w *= d);
}
inline vector3d operator/(const vector3d &v, double d) {
	vector3d w = v;
	return(w /= d);
}

inline vector3d &operator+=(vector3d &v, const vector3d &w) {
	v.x += w.x;
	v.y += w.y;
	v.z += w.z;
	v.w += w.w;
	return(v);
}
inline vector3d &operator-=(vector3d &v, const vector3d &w) {
  	v.x -= w.x;
	v.y -= w.y;
	v.z -= w.z;
	v.w -= w.w;
	return(v);
}

inline vector3d operator+(const vector3d &v, const vector3d &w) {
	vector3d u = v;
	return(u += w);
}
inline vector3d operator-(const vector3d &v, const vector3d &w) {
	vector3d u = v;
	return(u -= w);
}
double vector3d::dist(const vector3d &v) const {
  return((*this - v).abs());
}

#endif
