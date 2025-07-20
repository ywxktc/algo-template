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
        return findLastKnowningly(x, l, r, pred);
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
  i64 val = 0;
  Info() = default;
  Info &operator=(const Info &info) & = default;
  Info(i64 val) {
    this->val = val;
  }
  string String() const {
    return format("{{val={}}}", this->val);
  }
};

Info Combine(const Info &a, const Info &b) {
  Info c;
  c.val = max(a.val, b.val);
  return c;
}

// g++ -std=c++20 segment_tree.cpp -o segment_tree.exe && ./segment_tree.exe  && rm segment_tree.exe
int main() {
  {
    // [1] 默认值初始化, 每个节点都是默认值
    cout << "===== Test 1: Default Value Initialization =====\n";
    int n = 10;
    SegmentTree<Info> seg(n, Combine);
    cout << seg.String() << "\n";
  }

  {
    // [2] 数组初始化
    cout << "===== Test 2: Initialization with Vector =====\n";
    int n = 10;
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
      infos[i] = Info(i);
    }
    SegmentTree<Info> seg(infos, Combine);
    cout << seg.String() << "\n";
  }

  {
    // [3] Combine 函数支持匿名函数
    cout << "===== Test 3: Anonymous Combine Function =====\n";
    int n = 10;
    SegmentTree<Info> seg(n, [&](const Info &x, const Info &y) -> Info {
      Info c;
      c.val = x.val + y.val;
      return c;
    });
    cout << seg.String() << "\n";
  }

  {
    // [4] 获取区间 [1,6) 结果
    cout << "===== Test 4: Query Range [1,6) =====\n";
    int n = 10;
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
      infos[i] = Info(i);
    }
    SegmentTree<Info> seg(infos, [&](const Info &x, const Info &y) -> Info {
      Info c;
      c.val = x.val + y.val;
      return c;
    });
    auto info = seg.Get(1, 6);
    cout << info.String() << "\n";
  }

  {
    // [5] 修改下标为 3 的元素
    cout << "===== Test 5: Modify Element at Index 3 =====\n";
    int n = 10;
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
      infos[i] = Info(i);
    }
    SegmentTree<Info> seg(infos, [&](const Info &x, const Info &y) -> Info {
      Info c;
      c.val = x.val + y.val;
      return c;
    });
    seg.Modify(3, Info(9));
    cout << seg.Get(3).String() << "\n";
  }

  {
    // [6] 打印线段树结构
    cout << "===== Test 6: Print Segment Tree Structure =====\n";
    int n = 10;
    vector<Info> infos(n);
    for (int i = 0; i < n; i++) {
      infos[i] = Info(i);
    }
    SegmentTree<Info> seg(infos, [&](const Info &x, const Info &y) -> Info {
      Info c;
      c.val = x.val + y.val;
      return c;
    });
    cout << seg.String() << "\n";
  }

  return 0;
}