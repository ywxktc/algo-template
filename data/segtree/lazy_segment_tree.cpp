#include <bits/stdc++.h>

#include <format>
using namespace std;
using i64 = long long;

template <typename Info, typename Tag>
struct SegmentTree {
 public:
  using Combine = function<Info(const Info &, const Info &)>;
  using Predict = function<bool(const Info &)>;

  SegmentTree(int n, Combine comb, const Info &v = Info())
      : n(n), comb(comb), infos(2 * n - 1, v), tags(2 * n - 1) {
    Build(0, 0, n);
  }

  template <typename T>
  SegmentTree(vector<T> &v, Combine comb)
      : n(v.size()), comb(comb), infos(2 * n - 1), tags(2 * n - 1) {
    Build(0, 0, n, v);
  }

  Info Get(int l, int r) {
    assert(0 <= l && l < r && r <= n);
    return Get(0, 0, n, l, r);
  }

  Info Get(int p) {
    assert(0 <= p && p < n);
    return Get(0, 0, n, p, p + 1);
  }

  void Modify(int l, int r, const Tag &v) {
    assert(0 <= l && l < r && r <= n);
    Modify(0, 0, n, l, r, v);
  }

  void Modify(int p, const Tag &v) {
    assert(0 <= p && p < n);
    Modify(0, 0, n, p, p + 1, v);
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
        [&](int x, int l, int r, string prefix, string connector, bool is_last) {
          string label = (r - l == 1)
                             ? format("[{}] {} {}", l, infos[x].String(), tags[x].String())
                             : format("[{}, {}) {} {}", l, r, infos[x].String(), tags[x].String());
          oss << prefix << connector << label << '\n';

          if (r - l == 1) return;

          int m = (l + r) / 2;
          int y = x + 2 * (m - l);

          string next_prefix = prefix + (connector.empty() ? "" : (is_last ? "    " : "│   "));
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
  Combine comb;
  vector<Info> infos;
  vector<Tag> tags;

  void Build(int x, int l, int r) {
    if (r - l == 1)
      return;
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    Build(x + 1, l, m);
    Build(y, m, r);
    Pull(x, l, r);
  }

  template <typename T>
  void Build(int x, int l, int r, const vector<T> &v) {
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

  void Push(int x, int l, int r) {
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    Apply(x + 1, l, m, tags[x]);
    Apply(y, m, r, tags[x]);
    tags[x] = Tag();
  }

  void Pull(int x, int l, int r) {
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    infos[x] = comb(infos[x + 1], infos[y]);
  }

  void Apply(int x, int l, int r, const Tag &v) {
    infos[x].Apply(l, r, v);
    tags[x].Apply(l, r, v);
  }

  Info Get(int x, int l, int r, const int a, const int b) {
    if (a <= l && r <= b)
      return infos[x];
    Push(x, l, r);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    Info res{};
    if (b <= m)
      res = Get(x + 1, l, m, a, b);
    else if (a >= m)
      res = Get(y, m, r, a, b);
    else
      res = comb(Get(x + 1, l, m, a, b), Get(y, m, r, a, b));
    Pull(x, l, r);
    return res;
  }

  void Modify(int x, int l, int r, const int a, const int b, const Tag &v) {
    if (a <= l && r <= b) {
      Apply(x, l, r, v);
      return;
    }
    Push(x, l, r);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    if (b <= m)
      Modify(x + 1, l, m, a, b, v);
    else if (a >= m)
      Modify(y, m, r, a, b, v);
    else {
      Modify(x + 1, l, m, a, b, v);
      Modify(y, m, r, a, b, v);
    }
    Pull(x, l, r);
  }

  int FindFirst(int x, int l, int r, const int a, const int b, const Predict &pred) {
    if (a <= l && r <= b) {
      if (pred(infos[x]))
        return FindFirstKnowingly(x, l, r, pred);
      return -1;
    }
    Push(x, l, r);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    int res = -1;
    if (a < m)
      res = FindFirst(x + 1, l, m, a, b, pred);
    if (b >= m && res == -1)
      res = FindFirst(y, m, r, a, b, pred);
    Pull(x, l, r);
    return res;
  }

  int FindFirstKnowingly(int x, int l, int r, const Predict &pred) {
    if (r - l == 1)
      return l;
    Push(x, l, r);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    return pred(infos[x + 1]) ? FindFirstKnowingly(x + 1, l, m, pred)
                              : FindFirstKnowingly(y, m, r, pred);
  }

  int FindLast(int x, int l, int r, const int a, const int b, const Predict &pred) {
    if (a <= l && r <= b) {
      if (pred(infos[x]))
        return FindLastKnowingly(x, l, r, pred);
      return n;
    }
    Push(x, l, r);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    int res = n;
    if (b >= m)
      res = FindLast(x + 1, m, r, a, b, pred);
    if (a < m && res == n)
      res = FindLast(y, l, m, a, b, pred);
    Pull(x, l, r);
    return res;
  }

  int FindLastKnowingly(int x, int l, int r, const Predict &pred) {
    if (r - l == 1)
      return l;
    Push(x, l, r);
    int m = (l + r) / 2;
    int y = x + 2 * (m - l);
    return pred(infos[y]) ? FindLastKnowingly(y, m, r, pred)
                          : FindLastKnowingly(x + 1, l, m, pred);
  }
};

struct Tag {
  i64 add = 0;

  Tag() = default;
  Tag(i64 v) : add(v) {}
  Tag &operator=(const Tag &tag) = default;

  void Apply(int l, int r, const Tag &v) {
    add += v.add;
  }

  string String() const {
    return format("{{add={}}}", add);
  }
};

struct Info {
  i64 max_val = 0;

  Info() = default;
  Info(i64 v) : max_val(v) {}
  Info &operator=(const Info &info) = default;

  void Apply(int l, int r, const Tag &v) {
    max_val += v.add;
  }

  string String() const {
    return format("{{max={}}}", max_val);
  }
};

Info Combine(const Info &a, const Info &b) {
  return Info(max(a.max_val, b.max_val));
}

// g++ -std=c++20 lazy_segment_tree.cpp -o test && ./test && rm test
int main() {
  {
    cout << "===== Max Test 1: Init + Query =====\n";
    vector<Info> vals;
    for (int i = 0; i < 8; ++i) vals.emplace_back(i);
    SegmentTree<Info, Tag> seg(vals, Combine);
    cout << seg.String() << "\n";
    cout << "[3, 7) max = " << seg.Get(3, 7).String() << "\n\n";
  }

  {
    cout << "===== Max Test 2: Range Add + Query =====\n";
    int n = 8;
    SegmentTree<Info, Tag> seg(n, Combine);
    seg.Modify(2, 6, Tag(5));
    cout << seg.String() << "\n";
    cout << "[0, 8) max = " << seg.Get(0, 8).String() << "\n";
    cout << "[2, 6) max = " << seg.Get(2, 6).String() << "\n\n";
  }

  {
    cout << "===== Max Test 3: Increment Prefix & Check Lazy =====\n";
    int n = 10;
    SegmentTree<Info, Tag> seg(n, Combine);
    seg.Modify(0, 5, Tag(10));
    cout << "Prefix modified:" << seg.String() << "\n ";
    cout << "[5, 10) max = " << seg.Get(5, 10).String() << "\n";
    cout << "[0, 5) max = " << seg.Get(0, 5).String() << "\n\n";
  }

  return 0;
}