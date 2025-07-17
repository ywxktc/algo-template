#include <bits/stdc++.h>
using namespace std;

// 无向图找环
vector<int> FindCircle(vector<vector<int>> &g) {
  int n = g.size();
  vector<int> cycle, stk, vis(n, 0);
  function<bool(int, int)> Dfs = [&](int u, int p) -> bool {
    vis[u] = 1; // 标记为已访问
    stk.push_back(u);
    for (int v : g[u]) {
      if (v == p) {
        continue;
      }
      if (vis[v]) {
        do {
          cycle.push_back(stk.back());
          stk.pop_back();
        } while (cycle.back() != v);
        return true;
      }
      if (Dfs(v, u)) {
        return true;
      }
    }
    stk.pop_back();
    return false;
  };
  for (int i = 0; i < n; i++) {
    if (vis[i] == 0) {
      if (Dfs(i, -1)) {
        return cycle;
      }
    }
  }
  return {};
}

// 有向图找环
vector<int> FindDAGCircle(vector<vector<int>> &g) {
  int n = g.size();
  vector<int> cycle, stk, vis(n, 0);
  function<bool(int)> Dfs = [&](int u) -> bool {
    vis[u] = 1; // 标记为正在访问
    stk.push_back(u);
    for (int v : g[u]) {
      if (vis[v] == 2) {
        continue;
      }
      if (vis[v] == 1) {
        do {
          cycle.push_back(stk.back());
          stk.pop_back();
        } while (cycle.back() != v);
        return true;
      }
      if (Dfs(v)) {
        return true;
      }
    }
    vis[u] = 2; // 标记已访问
    stk.pop_back();
    return false;
  };
  for (int i = 0; i < n; i++) {
    if (vis[i] == 0) {
      if (Dfs(i)) {
        return cycle;
      }
    }
  }
  return {};
}

/*
    todo: 出度=入度=1的情况下简单的找环算法

    vector<int> cycle(n);
    vector<int> vis(n);
    for (int i = 0; i < n; i++) {
      if (vis[i]) {
        continue;
      }

      vector<int> path;
      int j = i;
      do {
        vis[j] = true;
        path.push_back(j);
        j = r[j];
      } while (!vis[j]);

      if (find(path.begin(), path.end(), j) != path.end()) {
        int x = j;
        do {
          cycle[x] = true;
          x = r[x];
        } while (x != j);
      }
    }

*/