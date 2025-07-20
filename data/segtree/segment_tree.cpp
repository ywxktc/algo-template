#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <typename Info>
struct SegmentTree {
 public:
  using Combine = function<Info(const Info &, const Info &)>;
  using Predict = function<bool(const Info &)>;

  // E.g.
  SegmentTree(int n, Combine comb, const Info &v = Info()) : n(n), comb(comb), infos(2 * n - 1, v) {
    Build(0, 0, n);
  }

  // E.g.
  // vector<Info> values = { Info(1), Info(2), Info(3), Info(4), Info(5) };
  // SegmentTree<Info> seg(values, Combine);
  SegmentTree(vector<Info> &v, Combine comb) : n(v.size()), comb(comb), infos(2 * n - 1) {
    Build(0, 0, n, v);
  }

  // Get [l, r)
  Info Get(int l, int r) {
    assert(0 <= l && l < r && r <= n);
    return Get(0, 0, n, l, r);
  }

  // Get [p]
  Info Get(int p) {
    assert(0 <= p && p < n);
    return Get(0, 0, n, p, p + 1);
  }

  void Modify(const int p, const Info &v) {
    assert(0 <= p && p < n);
    Modify(0, 0, n, p, v);
  }

  int FindFirst(const Predict &pred) {
    return FindFirst(0, 0, n, 0, n, pred);
  }

  int FindFirst(int l, int r, const Predict &pred) {
    assert(0 <= l && l < r && r <= n);
    return FindFirst(0, 0, n, l, r, pred);
  }

  int FindLast(const Predict &pred) {
    return FindLast(0, 0, n, 0, n, pred);
  }

  int FindLast(int l, int r, const Predict &pred) {
    assert(0 <= l && l < r && r <= n);
    return FindLast(0, 0, n, l, r, pred);
  }

  string String(bool wrap = true) const {
    ostringstream oss;

    function<void(int, int, int, string, string, bool)> PrintTree =
        [&](int x, int l, int r, string prefix, string connector, bool is_right_most) {
          string label = (r - l == 1)
                             ? format("[{}] {}", l, infos[x].String())
                             : format("[{}, {}) {}", l, r, infos[x].String());
          oss << prefix << connector << label << '\n';

          if (r - l == 1) return;

          int m = (l + r) / 2;
          int y = x + 2 * (m - l);

          string next_prefix = prefix + (connector.empty() ? "" : (is_right_most ? "    " : "│   "));
          PrintTree(x + 1, l, m, next_prefix, "├── ", false);
          PrintTree(y, m, r, next_prefix, "└── ", true);
        };

    if (wrap) oss << "{\n";
    PrintTree(0, 0, n, "", "", true);
    if (wrap) oss << "}";
    return oss.str();
  }

 private:
  int n;
  vector<Info> infos;
  Combine comb;

  void Build(int x, int l, int r) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      return;
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    Build(x + 1, l, m);
    Build(y, m, r);
    Pull(x, l, r);
  }

  void Build(int x, int l, int r, const vector<Info> &v) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      infos[x] = v[l];
      return;
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    Build(x + 1, l, m, v);
    Build(y, m, r, v);
    Pull(x, l, r);
  }

  void Pull(int x, int l, int r) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    infos[x] = comb(infos[x + 1], infos[y]);
  }

  Info Get(int x, int l, int r, const int a, const int b) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= a && a < b && b <= n);
    if (a <= l && r <= b) {
      return infos[x];
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    Info res{};
    if (b <= m) {
      res = Get(x + 1, l, m, a, b);
    } else {
      if (a >= m) {
        res = Get(y, m, r, a, b);
      } else {
        res = comb(Get(x + 1, l, m, a, b), Get(y, m, r, a, b));
      }
    }
    Pull(x, l, r);
    return res;
  }

  void Modify(int x, int l, int r, const int p, const Info &v) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= p && p < n);
    if (r - l == 1) {
      infos[x] = v;
      return;
    }
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (p < m) {
      Modify(x + 1, l, m, p, v);
    } else {
      Modify(y, m, r, p, v);
    }
    Pull(x, l, r);
  }

  int FindFirst(int x, int l, int r, const int a, const int b,
                const Predict &pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= a && a < b && b <= n);
    if (a <= l && r <= b) {
      if (pred(infos[x])) {
        return FindFirstKnowingly(x, l, r, pred);
      }
      return -1;
    }
    int res = -1;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (a < m) {
      res = FindFirst(x + 1, l, m, a, b, pred);
    }
    if (b >= m && res == -1) {
      res = FindFirst(y, m, r, a, b, pred);
    }
    Pull(x, l, r);
    return res;
  }

  int FindFirstKnowingly(int x, int l, int r, const Predict &pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      return l;
    }
    int res;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (pred(infos[x + 1])) {
      res = FindFirstKnowingly(x + 1, l, m, pred);
    } else {
      res = FindFirstKnowingly(y, m, r, pred);
    }
    Pull(x, l, r);
    return res;
  }

  int FindLast(int x, int l, int r, const int a, const int b,
               const Predict &pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    assert(0 <= a && a < b && b <= n);
    if (a <= l && r <= b) {
      if (pred(infos[x])) {
        return FindLastKnowingly(x, l, r, pred);
      }
      return n;
    }
    int res = n;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (b >= m) {
      res = FindLast(x + 1, m, r, a, b, pred);
    }
    if (a < m && res == n) {
      res = FindLast(y, l, r, a, b, pred);
    }
    Pull(x, l, r);
    return res;
  }

  int FindLastKnowingly(int x, int l, int r, const Predict &pred) {
    assert(0 <= x && x < 2 * n - 1);
    assert(0 <= l && l < r && r <= n);
    if (r - l == 1) {
      return l;
    }
    int res;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (pred(infos[y])) {
      res = FindLastKnowingly(y, m, r, pred);
    } else {
      res = FindLastKnowingly(x + 1, l, m, pred);
    }
    Pull(x, l, r);
    return res;
  }
};  // SegmentTree

struct Info {
  i64 mx = 0;
  Info() = default;
  Info &operator=(const Info &info) & = default;
  Info(i64 mx) {
    this->mx = mx;
  }
  string String() const {
    return format("{{mx={}}}", this->mx);
  }
};

Info Combine(const Info &a, const Info &b) {
  Info c;
  c.mx = max(a.mx, b.mx);
  return c;
}

// g++ -std=c++20 segment_tree.cpp -o segment_tree.exe && ./segment_tree.exe  && rm segment_tree.exe
int main() {
  {
    cout << "===== Test 1: Build with Vector & Print Tree =====\n";
    vector<Info> values = {5, 3, 8, 6, 1, 4, 7, 2};
    SegmentTree<Info> seg(values, Combine);
    cout << seg.String() << "\n\n";
  }

  {
    cout << "===== Test 2: Range Max Query =====\n";
    vector<Info> values = {5, 3, 8, 6, 1, 4, 7, 2};
    SegmentTree<Info> seg(values, Combine);
    cout << "[0, 4) max = " << seg.Get(0, 4).String() << "\n";  // 8
    cout << "[4, 8) max = " << seg.Get(4, 8).String() << "\n";  // 7
    cout << "[2, 5) max = " << seg.Get(2, 5).String() << "\n";  // 8
    cout << "\n";
  }

  {
    cout << "===== Test 3: Modify and Re-query =====\n";
    vector<Info> values = {5, 3, 8, 6, 1, 4, 7, 2};
    SegmentTree<Info> seg(values, Combine);

    seg.Modify(2, Info(10));  // 将原本的 8 改成 10
    cout << "After Modify(2, 10):\n";
    cout << seg.String() << "\n";
    cout << "[0, 4) max = " << seg.Get(0, 4).String() << "\n";  // 应该变成 10
    cout << "[1, 3) max = " << seg.Get(1, 3).String() << "\n";  // 应该是 10
    cout << "\n";
  }

  {
    cout << "===== Test 4: Find First Element >= 7 =====\n";
    vector<Info> values = {1, 2, 3, 7, 5, 9, 6, 4};
    SegmentTree<Info> seg(values, Combine);
    auto pred = [](const Info &x) { return x.mx >= 7; };
    int first = seg.FindFirst(pred);
    cout << "First index with val >= 7: " << first << "\n";  // 应该是 3
    cout << "\n";
  }

  {
    cout << "===== Test 5: Find Last Element >= 7 =====\n";
    vector<Info> values = {1, 2, 3, 7, 5, 9, 6, 4};
    SegmentTree<Info> seg(values, Combine);
    auto pred = [](const Info &x) { return x.mx >= 7; };
    int last = seg.FindLast(pred);
    cout << "Last index with val >= 7: " << last << "\n";  // 应该是 5
    cout << "\n";
  }

  return 0;
}