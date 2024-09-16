template<int m>
struct modint {
private:
  int _v = 0;
public:
  modint(): _v(0) {}

  template<typename T>
  modint(T v) {
    _v = (int) (v % m);
    if (_v < 0) {
      _v += m;
    }
  }

  int val() const { return _v; }

  modint& operator++() {
    _v++;
    if (_v >= m) {
      _v -= m;
    }
    return *this;
  }

  modint& operator--() {
    _v--;
    if (_v < 0) {
      _v += m;
    }
    return *this;
  }

  modint operator++(int) {
    modint res = *this;
    ++*this;
    return res;
  }

  modint operator--(int) {
    modint res = *this;
    --*this;
    return res;
  }

  modint& operator+=(const modint& rhs) {
    _v += rhs._v;
    if (_v >= m) {
      _v -= m;
    }
    return *this;
  }

  modint& operator-=(const modint& rhs) {
    _v -= rhs._v;
    if (_v < 0) {
      _v += m;
    }
    return *this;
  }

  modint& operator*=(const modint& rhs) {
    long long z = _v;
    z *= rhs._v;
    _v = (int) (z % m);
    return *this;
  }

  modint& operator/=(const modint& rhs) { return *this = *this * rhs.inv(); }

  modint operator+() const { return *this; }

  modint operator-() const { return modint() - *this; }

  template<typename T>
  modint pow(T n) const {
    assert(n >= 0);
    modint x = *this, r = 1;
    while(n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }

  modint inv() const { return exgcd(_v, m); }

  modint exgcd(int a, int b) const {
    int x = 0, y = 1;
    while (a != 0) {
      int t = b / a;
      b -= t * a;
      swap(a, b);
      x -= t * y;
      swap(x, y);
    }
    assert(b == 1);
    return modint(x);
  }

  friend modint operator+(const modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }

  friend modint operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs; }

  friend modint operator*(const modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }

  friend modint operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs; }

  friend bool operator==(const modint& lhs, const modint& rhs) { return lhs._v == rhs._v; }

  friend bool operator!=(const modint& lhs, const modint& rhs) { return lhs._v != rhs._v; }

  friend istream& operator>>(istream& in, modint<m>& x) {
    long long v;
    cin >> v;
    x = modint(v);
    return in;
  }
  
  friend ostream& operator<<(ostream& out, const modint<m>& x) {
    out << x._v;
    return out;
  }
}; // modint

const int mod = ;
using mint = modint<mod>;