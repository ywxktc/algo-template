struct DSU {
  vector<int> p;
  int n;

  DSU(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  int Find(int x) {
    while (x != p[x]) {
      x = p[x] = p[p[x]];
    }
    return x;
  }

  bool Merge(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};
