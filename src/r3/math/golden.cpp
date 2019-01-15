#include "golden.hpp"

const double tau = (std::sqrt(5.0) + 1) / 2;

#ifdef CPP20READY
#define LESS std::strong_ordering::less
#define MORE std::strong_ordering::greater
#define SAME std::strong_ordering::equal
std::strong_ordering operator<=>
#else
#define LESS -1
#define MORE 1
#define SAME 0
int cmp
#endif
(const golden &g1, const golden &g2) {
  golden g = g1 - g2;
  while(g.a < 0 && g.b > 0 || g.a > 0 && g.b < 0) {
    // The two parts have opposite sign.
    // So multiply by τ to get b + (a + b)τ, which is lower,
    // and repeat.
    fraction f = g.b + g.a;
    g.a = g.b;
    g.b = f;
  }
  // Now they don't, but one might be zero.
  if(g.a < 0 || g.b < 0)
    return(LESS);
  if(g.a > 0 || g.b > 0)
    return(MORE);
  return(SAME);
}

std::size_t hash_value(const golden &g) {
  size_t s = hash_value(g.a);
  boost::hash_combine(s, hash_value(g.b));
  return(s);
}
std::ostream &operator<<(std::ostream &os, const golden &g) {
  return(os << g.a << " + τ" << g.b);
}
std::istream &operator>>(std::istream &is, golden &g) {
  char c;
  return((is >> g.a).ignore(5) >> g.b);
}
golden &operator*=(golden &a, const golden &b) {
  fraction aa = a.a * b.a + a.b * b.b;
  a.b = a.a * b.b + a.b * (b.a + b.b);
  a.a = aa;
  return(a);
}
golden &operator/=(golden &a, const golden &b) {
  fraction d = b.a * (b.a + b.b) + b.b * b.b;
  fraction aa = (a.a * (b.a + b.b) - a.b * b.b) / d;
  a.b = (a.b * b.a - a.a * b.b) / d;
  a.a = aa;
  return(a);
}

std::size_t hash_value(const goldenVec4 &g) {
  size_t s = hash_value(g.x);
  boost::hash_combine(s, g.y);
  boost::hash_combine(s, g.z);
  boost::hash_combine(s, g.w);
  return(s);
}
std::ostream &operator<<(std::ostream &os, const goldenVec4 &v) {
  return(os << v.x << ',' << v.y << ',' << v.z << ',' << v.w);
}
std::istream &operator>>(std::istream &is, goldenVec4 &v) {
  char c;
  return(is >> v.x >> c >> v.y >> c >> v.z >> c >> v.w);
}

goldenVec4 goldenVec4::projectPerspective() const {
  static golden dist(-4,4);
  golden denom = dist - x;
  golden factor = denom <= (golden)0? (golden)1000 : dist / denom;
  return(goldenVec4(x * factor, y * factor, z * factor));  
}
