// https://www.luogu.com.cn/problem/P3388
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  int tot = 0;
  vector<int> dfn(n), low(n), ap(n);
  function<int(int, int)> Dfs = [&](int u, int fa) -> int {
    int children = 0;
    dfn[u] = low[u] = ++tot;
    for (int v : g[u]) {
      if (v == fa) {
        continue;
      }
      if (!dfn[v]) {
        children++;
        Dfs(v, u);
        if (dfn[u] <= low[v]) {
          ap[u] = 1;
        }
        low[u] = min(low[u], low[v]);
      } else {
        low[u] = min(low[u], dfn[v]);
      }
    }
    return children;
  };

  for (int u = 0; u < n; u++) {
    if (!dfn[u]) {
      ap[u] = Dfs(u, -1) > 1;
    }
  }

  vector<int> ans;
  for (int i = 0; i < n; i++) {
    if (ap[i]) {
      ans.push_back(i);
    }
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] + 1 << " \n"[i == ans.size() - 1];
  }
  return 0;
}
