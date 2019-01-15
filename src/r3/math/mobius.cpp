#include "mobius.hpp"
#include "utils.hpp"

using namespace std;

static mobius &normalize(mobius &m) {
  cmplx k = sqrt(m.a * m.d - m.b * m.c);
  m.a /= k;
  m.b /= k;
  m.c /= k;
  m.d /= k;
  return(m);
}

static mobius norm(const mobius &m) {
  cmplx k = sqrt(m.a * m.d - m.b * m.c);
  return(mobius(m.a / k, m.b / k, m.c / k, m.d / k));
}

mobius::mobius(cmplx z0, cmplx z1, cmplx z8, bool flip = false) : flip(flip) {
  if(flip) {
    z0 = conj(z0);
    z1 = conj(z1);
    z8 = conj(z8);
  }
  if(infinite(z0)) {
    a = 0;
    b = z8 - z1;
    c = -1;
    d = z8;
  } else if(infinite(z1)) {
    a = c = -1;
    b = z0;
    d = z8;
  } else if(infinite(z8)) {
    a = -1;
    b = z0;
    c = 0;
    d = z0 - z1;
  } else {
    b = -z0 * (a = z1 - z8);
    d = -z8 * (a = z1 - z0);
  }
  normalize(*this);
}

mobius mobius::isometry(geometry g, double angle, cmplx p) {
  if(infinite(p)) p = 100000;
  cmplx t = exp(cmplx(0,angle));
  return(mobius(t, p, conj(p) * t * ((int)g - 1), 1));
}
mobius mobius::pureTranslation(geometry g, cmplx p1, cmplx p2) {
  if(g == euclidean)
    return(mobius(1, p2 - p1, 0, 1));
  cmplx a = p2 - p1;
  cmplx b = p2 * p1 * ((int)g - 1);
  return(norm(isometry(g, 0, (conj(a) * b - a) / (norm(b) - 1))));
}

static double ident(double d) {
  return(d);
}

static double *(fromE[])(double) = {atan, ident, atanh};
static double *(toE[])(double) = {tan, ident, tanh};

mobius mobius::geodesic(geometry g, cmplx p1, cmplx p2, double factor = 1) {
  if(g == euclidean)
    return(mobius(1, (p2 - p1) * factor, 0, 1));
  mobius m1 = isometry(g, 0, -p1);
  cmplx p2t = m1.apply(p2);
  if(factor != 1) {
    double d = abs(p2t);
    p2t *= toE[(int)g](fromE[(int)g](d) * factor) / d;
  }
  return(isometry(g, 0, p1) * isometry(g, 0, p2t) * m1);
}
mobius mobius::hyperbolic(geometry g, cmplx fixedPlus, double sc) {
  if(g == euclidean)
    return(mobius(sc, (sc - 1) * fixedPlus, 0, 1));
  return(isometry(g, 0, fixedPlus) * scale(sc) * isometry(g, 0, -fixedPlus));
}
mobius mobius::hyperbolic(geometry g, cmplx fixedPlus,
			   cmplx point, double offset) {
  if(offset == 0)
    return(mobius());
  double d = abs(isometry(g, 0, -fixedPlus).apply(point));
  return(hyperbolic(g, fixedPlus, toE[(int)g](fromE[(int)g](d) + offset) / d));
}

mobius mobius::elliptic(geometry g, cmplx fixedPlus, double angle) {
  return(isometry(g, angle, fixedPlus) * isometry(g, 0, -fixedPlus));
}

mobius mobius::circleInv(cmplx center, double radius) {
  return(mobius(center, radius * radius - norm(center),
		1, -conj(center), true));
}
mobius mobius::lineFlip(cmplx p0, cmplx p1) {
  cmplx d = p1 - p0;
  cmplx p = p0 * conj(d);
  return(mobius(d, p - conj(p), 0, conj(d), true));
}
cmplx mobius::apply(cmplx z) const {
  if(infinite(z))
    if(c == 0)
      return(infcx);
    else
      return(a/c);
  if(flip)
    z = conj(z);
  z = (a * z + b) / (c * z + d);
  if(infinite(z))
    return(infcx);
  return(z);
}

static void conjAll(mobius &m) { 
    m.a = conj(m.a);
    m.b = conj(m.b);
    m.c = conj(m.c);
    m.d = conj(m.d);
} 

mobius mobius::inverse() const {
  mobius m(d, -b, -c, a, flip);
  if(flip) conjAll(m);
  return(m);
}

inline static vector3d conjQuat(vector3d v) {
  return(vector3d(v.x, -v.y, -v.z, -v.w));
}

static vector3d mulQuat(vector3d v, vector3d w) {
  vector3d r;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      r[i^j] += v[i] * w[j] * (i && j && (i - j + 4) % 3);
  return(r);
}

inline static vector3d divQuat(vector3d v, vector3d w) {
  return(mulQuat(v, conjQuat(w) / w.magSquared()));
}

vector3d mobius::applyToQuat(vector3d q) const {
  if(q.infinite())
    if(c == 0)
      return(infcx);
    else
      return(a/c);
  if(flip) {
    q.y = -q.y;
    q.z = -q.z;
    q.w = -q.w;
  }
  return(divQuat(mulQuat(a, q) + b, mulQuat(c, q) + d));
}
mobius operator*(const mobius &a, const mobius &b) {
  mobius aa = a;
  if(b.flip) {
    aa.flip = !aa.flip;
    conjAll(aa);
  }
  return(mobius(aa.a * b.a + aa.b * b.c, aa.a * b.b + aa.b * b.d,
		aa.c * b.a + aa.d * b.c, aa.c * b.b + aa.d * b.d, aa.flip));
}
