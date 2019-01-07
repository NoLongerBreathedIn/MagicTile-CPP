#ifndef UTILS_H
#define UTILS_H
#include <cmath>
extern const double threshhold;
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

#endif
