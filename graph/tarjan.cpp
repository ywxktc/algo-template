#include <bits/stdc++.h>
using namespace std;

struct Tarjan {
  int n = 0;                    // 顶点数量
  vector<vector<int>> adj;      // 邻接表
  vector<int> dfn, low, comp;   // 时间戳, low-link 值, 强连通分量编号
  vector<vector<int>> scc, dag; // 强连通分量, 压缩图

  Tarjan(int _n) : n(_n), adj(_n), dfn(_n, -1), low(_n), comp(_n, -1) {}

  void AddEdge(int u, int v) {
    assert(0 <= u && u < n && 0 <= v && v < n);
    adj[u].push_back(v);
  }

  const vector<vector<int>> &FindSCC() {
    int t = 0;
    stack<int> stk;
    vector<bool> in_stk(n);
    function<void(int)> Dfs = [&](int u) {
      dfn[u] = low[u] = t++;
      stk.push(u);
      in_stk[u] = true;
      for (int v : adj[u]) {
        if (dfn[v] == -1) {
          Dfs(v);
          low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
          low[u] = min(low[u], dfn[v]);
        }
      }
      if (dfn[u] == low[u]) {
        scc.push_back({});
        while (true) {
          int v = stk.top();
          stk.pop();
          in_stk[v] = false;
          comp[v] = scc.size() - 1;
          scc.back().push_back(v);
          if (v == u)
            break;
        }
      }
    };

    for (int u = 0; u < n; u++) {
      if (dfn[u] == -1)
        Dfs(u);
    }
    return scc;
  }

  const vector<vector<int>> &Compress() {
    dag.resize(scc.size());
    for (int u = 0; u < n; u++) {
      for (int v : adj[u]) {
        if (comp[u] != comp[v]) {
          dag[comp[u]].push_back(comp[v]);
        }
      }
    }
    for (auto &v : dag) {
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
    }
    return dag;
  }
};