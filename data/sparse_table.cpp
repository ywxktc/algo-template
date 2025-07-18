#include <bits/stdc++.h>
using namespace std;

template <typename T, class F = function<T(const T &, const T &)>>
class SparseTable {
public:
  int n;
  vector<vector<T>> mat; // mat[j][i] = func(a[i, i+(1<<j)-1])
  F func;

  // Usage:
  // vector<int> a(n);
  // SparseTable st(a, [&](int x, int y) { return max(x, y); });
  SparseTable(const vector<T> &a, const F &f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  // st.Get(l, r) returns func(a[l..r])
  T Get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};