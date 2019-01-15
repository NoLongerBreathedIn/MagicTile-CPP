#ifndef GOLDEN_H
#define GOLDEN_H
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/functional/hash.hpp>
#include "../geometry/vector3d.hpp"
#include "utils.hpp"
#include <cmath>
#ifdef CPP20READY
#include <compare>
#endif
#include <cstddef>
#include <ostream>
#include <istream>

extern const double tau;

struct golden {
  fraction a, b;
  inline golden(fraction a, fraction b = 0) :
    a(a), b(b) {}
  inline golden(int a) : a(a), b(0) {}
  inline operator double() const {
    return(boost::rational_cast<double>(a) +
	   tau * boost::rational_cast<double>(b));
  }
};
#ifdef CPP20READY
extern std::strong_ordering operator<=>(const golden &a, const golden &b);
#else
extern int cmp(const golden &a, const golden &b);
inline bool operator<(const golden &a, const golden &b) {
  return(cmp(a, b) < 0);
}
inline bool operator>(const golden &a, const golden &b) {
  return(cmp(a, b) > 0);
}
inline bool operator<=(const golden &a, const golden &b) {
  return(cmp(a, b) <= 0);
}
inline bool operator>=(const golden &a, const golden &b) {
  return(cmp(a, b) >= 0);
}
#endif
inline bool operator==(const golden &a, const golden &b) {
  return(a.a == b.a && a.b == b.b);
}

inline bool operator!=(const golden &a, const golden &b) {
  return(!(a == b));
}

extern std::size_t hash_value(const golden &g);
extern std::ostream &operator<<(std::ostream &os, const golden &g);
extern std::istream &operator>>(std::istream &is, golden &g);
inline golden &operator+=(golden &a, const golden &b) {
  a.a += b.a;
  a.b += b.b;
  return(a);
}
inline golden &operator-=(golden &a, const golden &b) {
  a.a -= b.a;
  a.b -= b.b;
  return(a);
}
inline golden operator+(const golden &a, const golden &b) {
  golden g = a;
  return(g += b);
}
inline golden operator-(const golden &a, const golden &b) {
  golden g = a;
  return(g -= b);
}
extern golden &operator*=(golden &a, const golden &b);
extern golden &operator/=(golden &a, const golden &b);
inline golden operator*(const golden &a, const golden &b) {
  golden g = a;
  return(g *= b);
}
inline golden operator/(const golden &a, const golden &b) {
  golden g = a;
  return(g /= b);
}
struct goldenVec4 {
  golden x, y, z, w;
  inline goldenVec4(golden x = 0, golden y = 0, golden z = 0, golden w = 0) :
    x(x), y(y), z(z), w(w) {}
  goldenVec4 projectPerspective() const;
  inline void projectOrthographic() {
    w = 0;
  }
  vector3d convertToReal() const {
    vector3d v(x, y, z, w);
    return(v);
  }
};

inline goldenVec4 &operator+=(goldenVec4 &a, const goldenVec4 &b) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  a.w += b.w;
  return(a);
}

inline goldenVec4 &operator-=(goldenVec4 &a, const goldenVec4 &b) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  a.w -= b.w;
  return(a);
}


inline goldenVec4 operator+(const goldenVec4 &a, const goldenVec4 &b) {
  goldenVec4 v = a;
  return(v += b);
}

inline goldenVec4 operator-(const goldenVec4 &a, const goldenVec4 &b) {
  goldenVec4 v = a;
  return(v -= b);
}

inline goldenVec4 &operator*=(goldenVec4 &v, const golden &g) {
  v.x *= g;
  v.y *= g;
  v.z *= g;
  v.w *= g;
  return(v);
}

inline goldenVec4 &operator/=(goldenVec4 &v, const golden &g) {
  v.x /= g;
  v.y /= g;
  v.z /= g;
  v.w /= g;
  return(v);
}

inline goldenVec4 operator*(const goldenVec4 &v, const golden &g) {
  goldenVec4 w = v;
  return(w *= g);
}

inline goldenVec4 operator*(const golden &g, const goldenVec4 &v) {
  goldenVec4 w = v;
  return(w *= g);
}

inline goldenVec4 operator/(const goldenVec4 &v, const golden &g) {
  goldenVec4 w = v;
  return(w /= g);
}

inline bool operator==(const goldenVec4 &a, const goldenVec4 &b) {
  return(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w);
}

inline bool operator!=(const goldenVec4 &a, const goldenVec4 &b) {
  return(!(a == b));
}

extern std::size_t hash_value(const goldenVec4 &g);
extern std::ostream &operator<<(std::ostream &os, const goldenVec4 &v);
extern std::istream &operator>>(std::istream &is, goldenVec4 &v);
#endif
