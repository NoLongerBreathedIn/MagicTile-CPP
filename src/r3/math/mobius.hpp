#ifndef MOBIUS_H
#define MOBIUS_H
#include <complex>
#include "../geometry/geometry2d.hpp"
#include "../geometry/vector3d.hpp"

typedef std::complex<double> cmplx;

// TODO: Add circleInv(Circle), fromTwoPolygons
struct mobius;
struct mobius {
  cmplx a, b, c, d;
  bool flip;
  static mobius uhp(1-1i, 1+1i, 1+1i, 1-1i);
  static mobius reflectX(1,0,0,1,true);
  inline mobius() : a(1), b(0), c(0), d(1), flip(false) {}
  inline mobius(cmplx a, cmplx b, cmplx c, cmplx d, bool flip = false) :
    a(a), b(b), c(c), d(d), flip(flip) {}
  mobius(cmplx z0, cmplx z1, cmplx z8, bool flip = false);
  // takes z0 to 0, z1 to 1, z8 to infinity
  static mobius isometry(geometry g, double angle, cmplx p);
  static mobius pureTranslation(geometry g, cmplx p1, cmplx p2);
  static mobius geodesic(geometry g, cmplx p1, cmplx p2, double factor = 1);
  static mobius hyperbolic(geometry g, cmplx fixedPlus, double scale);
  static mobius hyperbolic(geometry g, cmplx fixedPlus,
			   cmplx point, double offset);
  static mobius elliptic(geometry g, cmplx fixedPlus, double angle);
  static mobius circleInv(cmplx center, double radius);
  static mobius lineFlip(cmplx p0, cmplx p1);
  cmplx apply(cmplx z) const;
  mobius inverse() const;
  inline static mobius scale(double s) {
    return(mobius(s,0,0,1));
  }
  inline vector3d apply(vector3d z) const {
    return(apply((cmplx)z));
  }
  vector3d applyToQuat(vector3d q) const;
  inline cmplx trace() const {
    return(a+d);
  }
  inline cmplx traceSq() const {
    cmplx t = trace();
    return(t * t);
  }
};

extern mobius operator*(const mobius &a, const mobius &b);
inline mobius operator/(const mobius &a, const mobius &b) {
  return(a / b.inverse());
}
inline mobius &operator*=(mobius &a, const mobius &b) {
  return(a = a * b);
}
inline mobius &operator/=(mobius &a, const mobius &b) {
  return(a = a / b);
}
  
#endif
