struct Tarjan {
  int n = 0; // 顶点数量
  vector<vector<int>> g; // 邻接图
  vector<int> id; // 顶点编号
  vector<int> low; // low-link值
  vector<int> scc_id; // 顶点强连通分量编号
  vector<vector<int>> scc; // 强联通分量
  vector<vector<int>> scc_g; // 压缩后的强连通分量

  Tarjan(int _n) : n(_n), g(_n), id(_n, -1), low(_n), scc_id(_n, -1) {}

  void AddEdge(int u, int v) {
    assert(0 <= u && u < n && 0 <= v && v < n);
    g[u].push_back(v);
  }

  const vector<vector<int>>& FindSCC() {
    int timer = 0;
    stack<int> stk;
    vector<bool> instk(n);
    function<void(int)> Dfs = [&](int u) {
      id[u] = low[u] = timer++;
      stk.push(u);
      instk[u] = true;

      for (int v : g[u]) {
        if (id[v] == -1) {
          Dfs(v);
          low[u] = min(low[u], low[v]);
        } else if (instk[v]) {
          low[u] = min(low[u], id[v]);
        }
      }

      if (id[u] == low[u]) {
        scc.push_back({});
        while (true) {
          int v = stk.top();
          stk.pop();
          instk[v] = false;
          scc_id[v] = scc.size() - 1;
          scc.back().push_back(v);
          if (v == u) break;
        }
      }
    };

    for (int u = 0; u < n; u++) {
      if (id[u] == -1) {
        Dfs(u);
      }
    }

    return scc;
  }

  const vector<vector<int>>& Compress() {
    scc_g.resize(scc.size());
    for (int u = 0; u < n; u++) {
      for (int v : g[u]) {
        if (scc_id[u] != scc_id[v]) {
          scc_g[scc_id[u]].push_back(scc_id[v]);
        }
      }
    }
    for (auto &adj : scc_g) {
      sort(adj.begin(), adj.end());
      adj.erase(unique(adj.begin(), adj.end()), adj.end());
      adj.shrink_to_fit();
    }
    return scc_g;
  }
};
