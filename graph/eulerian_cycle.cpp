#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename Node>
class EulerianCycle {
public:
  // 邻接表：支持 multiset 保证字典序（可改为 vector）
  unordered_map<Node, vector<Node>> graph;
  vector<Node> path;

  // 添加有向边 u -> v
  void add_edge(const Node &u, const Node &v) {
    graph[u].push_back(v);
  }

  // 构建欧拉回路，从指定起点出发
  void build(const Node &start) {
    dfs(start);
    reverse(path.begin(), path.end());
  }

  // 获取欧拉路径
  vector<Node> get_path() const {
    return path;
  }

private:
  void dfs(const Node &u) {
    auto &edges = graph[u];
    while (!edges.empty()) {
      Node v = edges.back();
      edges.pop_back();
      dfs(v);
    }
    path.push_back(u);
  }
};