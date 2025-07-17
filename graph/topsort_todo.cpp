#include <bits/stdc++.h>
using namespace std;

vector<int> Topsort(vector<vector<int>> &dag) {
  int n = dag.size();
  vector<int> deg(n, 0);
  for (int u = 0; u < n; u++) {
    for (int v : dag[u]) {
      deg[v]++;
    }
  }
  queue<int> q;
  for (int u = 0; u < n; u++) {
    if (deg[u] == 0) {
      q.push(u);
    }
  }

  vector<int> ret;
  while (!q.empty()) {
    int f = q.front();
    q.pop();
    ret.push_back(f);
    for (int v : dag[f]) {
      deg[v]--;
      if (deg[v] == 0) {
        q.push(v);
      }
    }
  }
  return ret;
}

stack<int> TopsortStk(vector<vector<int>> &dag) {
  int n = dag.size();
  vector<bool> vis(n);
  stack<int> stk;
  function<void(int)> Dfs = [&](int u) {
    if (vis[u]) {
      return;
    }
    for (int v : dag[u]) {
      if (!vis[v]) {
        Dfs(v);
      }
    }
    stk.push(u);
  };
  for (int u = 0; u < n; u++) {
    if (!vis[u]) {
      Dfs(u);
    }
  }
  return stk;
}