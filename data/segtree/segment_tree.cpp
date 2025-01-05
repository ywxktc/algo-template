template <typename Info>
struct SegmentTree {
 public:
  using Combine = function<Info(const Info&, const Info&)>;
  using Predict = function<bool(const Info&)>;

  // E.g.
  // SegmentTree<Info> seg(n, Combine);
  SegmentTree(int n, Combine comb, const Info& v = Info()) : n(n), comb(comb), info(2 * n - 1, v) {
    build(0, 0, n);
  }

  // E.g.
  // vector<Info> values = { Info(1), Info(2), Info(3), Info(4), Info(5) };
  // SegmentTree<Info> seg(values, Combine);
  SegmentTree(vector<Info>& v, Combine comb) : n(v.size()), comb(comb), info(2 * n - 1) {
    build(0, 0, n, v);
  }

  // Get [l, r)
  Info Get(int l, int r) {
    assert(0 <= l && l < r && r <= n);
    return get(0, 0, n, l, r);
  }

  // Get [p]
  Info Get(int p) {
    assert(0 <= p && p < n);
    return get(0, 0, n, p, p + 1);
  }

  void Modify(const int p, const Info& v) {
    assert(0 <= p && p < n);
    modify(0, 0, n, p, v);
  }

  int FindFirst(const Predict& pred) { return findFirst(0, 0, n, 0, n, pred); }

  int FindFirst(int l, int r, const Predict& pred) {
    assert(0 <= l && l < r && r <= n);
    return findFirst(0, 0, n, l, r, pred);
  }

  int FindLast(const Predict& pred) { return findLast(0, 0, n, 0, n, pred); }

  int FindLast(int l, int r, const Predict& pred) {
    assert(0 <= l && l < r && r <= n);
    return findLast(0, 0, n, l, r, pred);
  }

 private:
  int n;
  vector<Info> info;
  Combine comb;

  void build(int x, int l, int r) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      return;
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    build(x + 1, l, m);
    build(y, m, r);
    pull(x, l, r);
  }

  void build(int x, int l, int r, const vector<Info>& v) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      info[x] = v[l];
      return;
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    build(x + 1, l, m, v);
    build(y, m, r, v);
    pull(x, l, r);
  }

  void pull(int x, int l, int r) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    info[x] = comb(info[x + 1], info[y]);
  }

  Info get(int x, int l, int r, const int a, const int b) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= a && a < b && b <= n);
    if (a <= l && r <= b) {
      return info[x];
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    Info res{};
    if (b <= m) {
      res = get(x + 1, l, m, a, b);
    } else {
      if (a >= m) {
        res = get(y, m, r, a, b);
      } else {
        res = comb(get(x + 1, l, m, a, b), get(y, m, r, a, b));
      }
    }
    pull(x, l, r);
    return res;
  }

  void modify(int x, int l, int r, const int p, const Info& v) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= p && p < n);
    if (r - l == 1) {
      info[x] = v;
      return;
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (p < m) {
      modify(x + 1, l, m, p, v);
    } else {
      modify(y, m, r, p, v);
    }
    pull(x, l, r);
  }

  int findFirst(int x, int l, int r, const int a, const int b,
                const Predict& pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= a && a < b && b <= n);
    if (a <= l && r <= b) {
      if (pred(info[x])) {
        return findFirstKnowingly(x, l, r, pred);
      }
      return -1;
    }
    int res = -1;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (a < m) {
      res = findFirst(x + 1, l, m, a, b, pred);
    }
    if (b >= m && res == -1) {
      res = findFirst(y, m, r, a, b, pred);
    }
    pull(x, l, r);
    return res;
  }

  int findFirstKnowingly(int x, int l, int r, const Predict& pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      return l;
    }
    int res;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (pred(info[x + 1])) {
      res = findFirstKnowingly(x + 1, l, m, pred);
    } else {
      res = findFirstKnowingly(y, m, r, pred);
    }
    pull(x, l, r);
    return res;
  }

  int findLast(int x, int l, int r, const int a, const int b,
               const Predict& pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= a && a < b && b <= n);
    if (a <= l && r <= b) {
      if (pred(info[x])) {
        return findLastKnowningly(x, l, r, pred);
      }
      return n;
    }
    int res = n;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (b >= m) {
      res = findLast(x + 1, m, r, a, b, pred);
    }
    if (a < m && res == n) {
      res = findLast(y, l, r, a, b, pred);
    }
    pull(x, l, r);
    return res;
  }

  int findLastKnowingly(int x, int l, int r, const Predict& pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      return l;
    }
    int res;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (pred(info[y])) {
      res = findLastKnowingly(y, m, r, pred);
    } else {
      res = findLastKnowingly(x + 1, l, m, pred);
    }
    pull(x, l, r);
    return res;
  }
};  // SegmentTree

struct Info {
  i64 val = 0;
  
  Info() : val(0) {}
  
  Info(i64 val) : val(val) {}
  
  Info& operator=(const Info& info) & {
    val = info.val;
    return *this;
  }
};

Info Combine(const Info& a, const Info& b) {
  Info c;
  c.val = max(a.val, b.val);
  return c;
}


