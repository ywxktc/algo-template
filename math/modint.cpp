#include <bits/stdc++.h>
using namespace std;

template <int m>
struct ModInt {
 private:
  int _v = 0;

 public:
  ModInt() : _v(0) {}

  template <typename T>
  ModInt(T v) {
    _v = (int)(v % m);
    if (_v < 0) {
      _v += m;
    }
  }

  int val() const { return _v; }

  ModInt &operator++() {
    _v++;
    if (_v >= m) {
      _v -= m;
    }
    return *this;
  }

  ModInt &operator--() {
    _v--;
    if (_v < 0) {
      _v += m;
    }
    return *this;
  }

  ModInt operator++(int) {
    ModInt res = *this;
    ++*this;
    return res;
  }

  ModInt operator--(int) {
    ModInt res = *this;
    --*this;
    return res;
  }

  ModInt &operator+=(const ModInt &rhs) {
    _v += rhs._v;
    if (_v >= m) {
      _v -= m;
    }
    return *this;
  }

  ModInt &operator-=(const ModInt &rhs) {
    _v -= rhs._v;
    if (_v < 0) {
      _v += m;
    }
    return *this;
  }

  ModInt &operator*=(const ModInt &rhs) {
    long long z = _v;
    z *= rhs._v;
    _v = (int)(z % m);
    return *this;
  }

  ModInt &operator/=(const ModInt &rhs) { return *this = *this * rhs.inv(); }

  ModInt operator+() const { return *this; }

  ModInt operator-() const { return ModInt() - *this; }

  template <typename T>
  ModInt pow(T n) const {
    assert(n >= 0);
    ModInt x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }

  ModInt inv() const { return exgcd(_v, m); }

  ModInt exgcd(int a, int b) const {
    int x = 0, y = 1;
    while (a != 0) {
      int t = b / a;
      b -= t * a;
      swap(a, b);
      x -= t * y;
      swap(x, y);
    }
    assert(b == 1);
    return ModInt(x);
  }

  friend ModInt operator+(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) += rhs;
  }

  friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) -= rhs;
  }

  friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) *= rhs;
  }

  friend ModInt operator/(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) /= rhs;
  }

  friend bool operator==(const ModInt &lhs, const ModInt &rhs) {
    return lhs._v == rhs._v;
  }

  friend bool operator!=(const ModInt &lhs, const ModInt &rhs) {
    return lhs._v != rhs._v;
  }

  friend istream &operator>>(istream &in, ModInt<m> &x) {
    long long v;
    cin >> v;
    x = ModInt(v);
    return in;
  }

  friend ostream &operator<<(ostream &out, const ModInt<m> &x) {
    out << x._v;
    return out;
  }
};  // ModInt

const int mod = 1e9 + 7;
using Z = ModInt<mod>;
