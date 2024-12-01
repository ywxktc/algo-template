#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  int tot = 0;
  vector<int> dfn(n), low(n);
  vector<pair<int, int>> br;
  function<void(int, int)> Dfs = [&](int u, int fa) {
    dfn[u] = low[u] = ++tot;
    for (int v : g[u]) {
      if (v == fa) {
        continue;
      }
      if (!dfn[v]) {
        Dfs(v, u);
        if (dfn[u] < low[v]) {
          br.emplace_back(u, v);
        }
        low[u] = min(low[u], low[v]);
      } else {
        low[u] = min(low[u], dfn[v]);
      }
    }
  };

  for (int i = 0; i < n; i++) {
    if (!dfn[i]) {
      Dfs(i, -1);
    }
  }

  for (int i = 0; i < br.size(); i++) {
    if (br[i].first > br[i].second) {
      swap(br[i].first, br[i].second);
    }
  }
  sort(br.begin(), br.end());
  for (auto [a, b] : br) {
    cout << a + 1 << " " << b + 1 << "\n";
  }
  return 0;
}
