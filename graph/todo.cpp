template<typename T>
struct Edge {
  int from;
  int to;
  T cost;
};

template<typename T>
struct Graph {
  int n = 0;
  int m = 0;
  vector<Edge<T>> edges;
  vector<vector<int>> g;

  Graph(int _n) : n(_n), g(_n) {}

  virtual void AddEdge(int from, int to, T cost) = 0;
};

template<typename T>
struct DirectedGraph : public Graph<T> {
  using Graph<T>::n;
  using Graph<T>::m;
  using Graph<T>::edges;
  using Graph<T>::g;

  DirectedGraph(int _n) : Graph(_n) {}

  void AddEdge(int from, int to, T cost = 1) override {
    edges.push_back({from, to, cost});
    g[from].push_back(m);
    m++;
  }
};

template<typename T>
struct UndirectedGraph : public Graph<T> {
  using Graph<T>::n;
  using Graph<T>::m;
  using Graph<T>::edges;
  using Graph<T>::g;

  UndirectedGraph(int _n) : Graph(_n) {}

  void AddEdge(int from, int to, T cost = 1) override {
    edges.push_back({from, to, cost});
    g[from].push_back(m);
    g[to].push_back(m);
    m++;
  }
};