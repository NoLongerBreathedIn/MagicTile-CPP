#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <complex>
#include <ostream>

class vector3d {
public:
  inline vector3d(double x, double y, double z = 0, double w = 0) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
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
  inline double dist(const vector3d &v) {
    return((*this - v).abs());
  }
  double dot(const vector3d &v) const;
};

inline bool operator==(const vector3d &a, const vector3d &b) {
  return(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}
inline bool operator!=(const vector3d &a, const vector3d &b) {
  return(!(a == b));
}

extern std::size_t hash_value(const vector3d &v);

extern std::ostream &operator<<(std::ostream &os, const vector3d &v);

extern vector3d operator*(const vector3d &v, double d);
extern vector3d operator*(double d, const vector3d &v);
extern vector3d operator/(const vector3d &v, double d);
extern vector3d &operator*=(vector3d &v, double d);
extern vector3d &operator/=(vector3d &v, double d);
extern vector3d operator+(const vector3d &v, const vector3d &w);
extern vector3d operator-(const vector3d &v, const vector3d &w);
extern vector3d &operator+=(vector3d &v, const vector3d &w);
extern vector3d &operator-=(vector3d &v, const vector3d &w);

#endif
