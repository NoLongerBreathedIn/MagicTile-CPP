#ifndef UTILS_H
#define UTILS_H
#include <cmath>
#include <boost/rational.hpp>
#include <boost/functional/hash.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <complex>
typedef boost::rational<boost::multiprecision::cpp_int> fraction;
extern const double threshhold;
extern const std::complex<double> infcx;
inline bool getol(double a, double b, double th = threshhold) {
  return(a - b > -th);
}
inline bool letol(double a, double b, double th = threshhold) {
  return(a - b < th);
}
inline bool gttol(double a, double b, double th = threshhold) {
  return(a - b > th);
}
inline bool lttol(double a, double b, double th = threshhold) {
  return(a - b < -th);
}
inline bool eqtol(double a, double b = 0, double th = threshhold) {
  return(std::abs(a - b) < th);
}
inline double h2enorm(double h) {
  return(std::isnan(h)? 1 : std::tanh(h/2));
}
inline double e2hnorm(double e) {
  return(2 * std::atanh(e));
}
inline bool infinite(std::complex<double> c) {
  return(!(std::isfinite(c.real()) && std::isfinite(c.imag())));
}

template<typename t>
std::size_t hash_value(const boost::rational<t> &r) {
  size_t s = boost::hash<t>()(r.numerator());
  boost::hash_combine(s, r.denominator());
  return(s);
}

#endif
