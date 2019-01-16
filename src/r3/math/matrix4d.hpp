#ifndef MATRIX4D_H
#define MATRIX4D_H
#include "../geometry/vector3d.hpp"

// TODO: VectorND?

struct matrix4d {
  double data[4][4];
  inline double *operator[](int ix) {
    return(data[ix]);
  }
  inline const double *operator[](int ix) const {
    return(data[ix]);
  }
  inline matrix4d() :
    data({{1,0,0,0},
	  {0,1,0,0},
	  {0,0,1,0},
	  {0,0,0,1}}) {}
  matrix4d transpose() const;
  matrix4d gramSchmidt() const;
  matrix4d gramSchmidt(double (*inner)(const double *, const double *)) const;
  matrix4d gramSchmidt(double (*inner)(const double *, const double *),
		       void (*normalize)(double *)) const;
  static matrix4d rotateInPlane(double angle, int c1, int c2);
};

extern matrix4d &operator+=(matrix4d &m1, const matrix4d &m2);
inline matrix4d operator+(const matrix4d &m1, const matrix4d &m2) {
  matrix4d m = m1;
  return(m += m2);
}

extern matrix4d operator*(const matrix4d &m1, const matrix4d &m2);
extern matrix4d &operator*=(matrix4d &m, double d);
extern matrix4d &operator/=(matrix4d &m, double d);
inline matrix4d &operator*=(matrix4d &m1, const matrix4d &m2) {
  return(m1 = m1 * m2);
}
inline matrix4d operator*(const matrix4d &m, double d) {
  matrix4d mm = m;
  return(mm *= d);
}
inline matrix4d operator*(double d, const matrix4d &m) {
  matrix4d mm = m;
  return(mm *= d);
}
inline matrix4d operator/(const matrix4d &m, double d) {
  matrix4d mm = m;
  return(mm /= d);
}

extern vector3d operator*(const matrix4d &m, const vector3d &v);


#endif
