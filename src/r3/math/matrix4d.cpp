#include "matrix4d.hpp"
#include <cmath>
using namespace std;

matrix4d matrix4d::transpose() const {
  matrix4d y;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      y.data[i][j] = data[j][i];
  return(y);
}

static double dp(const double *x, const double *y) {
  double d = 0;
  for(int i = 0; i < 4; i++)
    d += x[i] * y[i];
}

static void (*norm(double (*inner)(const double *,
				   const double *)))(double *) {
  return([inner](double *ds) {
	   double d = sqrt(inner(ds, ds));
	   for(int i = 0; i < 4; i++)
	     ds[i] /= d;
	 });
}// my god currying is ugly in C++.

matrix4d matrix4d::gramSchmidt() const {
  return(gramSchmidt(dp));
}

matrix4d matrix4d::gramSchmidt(double (*inner)(const double *,
					       const double *)) const {
  return(gramSchmidt(inner, norm(inner)));
}

matrix4d matrix4d::gramSchmidt(double (*inner)(const double *, const double *),
			       void (*normalize)(double *)) const {
  matrix4d m = *this;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < i; j++) {
      double d = inner(m.data[i], m.data[j]);
      for(int k = 0; k < 4; k++)
	m.data[i][k] -= m.data[j][k] * d;
    }
    normalize(m.data[i]);
  }
  return(m);
}

matrix4d matrix4d::rotateInPlane(double angle, int c1, int c2) {
  matrix4d m;
  m.data[c1][c1] = m.data[c2][c2] = cos(angle);
  m.data[c1][c2] = -(m.data[c2][c1] = sin(angle));
  return(m);
}

matrix4d &operator+=(matrix4d &m1, const matrix4d &m2) {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      m1.data[i][j] += m2.data[i][j];
  return(m1);
}

matrix4d operator*(const matrix4d &m1, const matrix4d &m2) {
  matrix4d m;
  for(int i = 0; i < 4; i++)
    m.data[i][i] = 0;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      for(int k = 0; k < 4; k++)
	m.data[i][k] += m1.data[i][j] * m2.data[j][k];
  return(m);
}
  
matrix4d &operator*=(matrix4d &m, double d) {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      m.data[i][j] *= d;
  return(m);
}
matrix4d &operator/=(matrix4d &m, double d) {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      m.data[i][j] *= d;
  return(m);
}

vector3d operator*(const matrix4d &m, const vector3d &v) {
  vector3d w;
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 4; j++)
      w[i] += m.data[i][j] * v[j];
  return(w);
}
