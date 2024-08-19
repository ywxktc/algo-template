template<int m>
class modint {
private:
  int _v = 0;
public:
  modint(): _v(0) {}
  modint(int v) { 
    _v = v % m;
    if (_v < 0) {
      _v += m;
    }
  }
  void norm() {
    this->_v = this->_v % m;
    if (this->_v < 0) {
      this->_v += m;
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
  modint operator-() const {return modint() - *this;}
  modint pow(long long n) const {
    assert(n >= 0);
    modint x = *this, r = 1;
    while(n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  modint exgcd(int a, int b) const {
    int x = 0, y = 1;
    while (a != 0) {
      int t = b / a;
      b -= t * a; swap(a, b);
      x -= t * y; swap(x, y);
    }
    assert(b == 1);
    return modint(x);
  }
  modint inv() const { return exgcd(_v, m); }
  friend modint operator+(const modint& lhs, const modint& rhs) { return modint(lhs) += rhs; }
  friend modint operator-(const modint& lhs, const modint& rhs) { return modint(lhs) -= rhs; }
  friend modint operator*(const modint& lhs, const modint& rhs) { return modint(lhs) *= rhs; }
  friend modint operator/(const modint& lhs, const modint& rhs) { return modint(lhs) /= rhs; }
  friend bool operator==(const modint& lhs, const modint& rhs) { return lhs._v == rhs._v; }
  friend bool operator!=(const modint& lhs, const modint& rhs) { return lhs._v != rhs._v; }
  friend istream& operator>>(istream& in, modint<m>& x) { cin >> x._v; x.norm(); return in; }
  friend ostream& operator<<(ostream& out, const modint<m>& x) { out << x._v; return out; }
};

template<typename T>
struct Binom {
  vector<T> fact;
  vector<T> inv_fact;
  void adaptive(int m) {
    for (int i = fact.size(); i <= m; i++) {
      fact.push_back(i == 0 ? T(1) : T(i) * fact[i - 1]);
      inv_fact.push_back(1 / fact.back());
    }
  }
  T operator() (int m, int n) {
    assert(m >= n);
    adaptive(m);
    return fact[m] * inv_fact[n] * inv_fact[m - n];
  }
};

using mint = modint<>;
Binom<mint> C;
