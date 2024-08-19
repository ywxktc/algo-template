#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  const int maxa = 1e6;
  vector<int> cnt(maxa + 1);

  int t;
  cin >> t;
  while (t--) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    fill(cnt.begin(), cnt.end(), 0);

    // 块大小
    const int block_size = max((int) sqrt(n), (int) (n / sqrt(q)));

    // 所有请求
    vector<array<int, 3>> ask;
    for (int i = 0; i < q; i++) {
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      ask.push_back({l, r, i});
    }
    // 莫队排序
    sort(ask.begin(), ask.end(), [&](array<int, 3> &a, array<int, 3> &b) {
      int block_a = a[0] / block_size;
      int block_b = b[0] / block_size;
      if (block_a != block_b) {
        return block_a < block_b;
      }
      if (block_a % 2 == 0) {
        return a[1] < b[1];
      } else {
        return a[1] > b[1];
      }
    });

    // 开始执行

    int l = 0, r = -1, odd = 0;
    auto add = [&](int pos, int delta) {
      cnt[a[pos]] += delta;
      if (cnt[a[pos]] % 2 == 0) {
        odd--;
      } else {
        odd++;
      }
    };

    vector<bool> ans(q);
    for (auto& [ql, qr, idx] : ask) {
      while (l < ql) add(l++, -1);
      while (l > ql) add(--l, +1);
      while (r < qr) add(++r, +1);
      while (r > qr) add(r--, -1);
      ans[idx] = (odd == 0);
    }

    for (int i = 0; i < q; i++) {
      cout << (ans[i] ? "YES": "NO") << '\n';
    }
  }
  return 0;
}