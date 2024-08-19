template <typename T>
struct Fenwick {
  int n, m;
  vector<T> fenw;

  Fenwick(int _n) {
    n = _n;
    m = bit_floor(unsigned(n));
    fenw.resize(n);
  }

  // Adds value `v` to element at index `x`
  void Add(int x, const T &v) {
    assert(0 <= x && x < n);
    while (x < n) {
      fenw[x] += v;
      x |= x + 1;
    }
  }

  // Returns sum of elements in range [0,x)
  T Get(int x) {
    assert(0 <= x && x <= n);
    T ret{};
    while (x > 0) {
      ret += fenw[x - 1];
      x &= x - 1;
    }
    return ret;
  }

  // Returns sum of elements in range [l, r)
  T Get(int l, int r) { return Get(r) - Get(l); }

  // Returns maximum index `at` where sum of elements in range [0, at) <= `c`
  int Select(const T &c) {
    T v{};
    int at = 0;
    for (int len = m; len > 0; len >>= 1) {
      if (at + len <= n && v + fenw[at + len - 1] <= c) {
        v += fenw[at + len - 1];
        at += len;
      }
    }
    return at;
  }
};
