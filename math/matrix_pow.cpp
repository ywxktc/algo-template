template <typename T>
vector<vector<T>> Pow(vector<vector<T>> a, long long p) {
  assert(a.size() == a[0].size());
  int n = a.size();

  vector<vector<T>> res(n, vector<T>(n));
  for (int i = 0; i < n; i++) {
    res[i][i] = 1;
  }

  while (p) {
    if (p & 1) {
      res = Mul(res, a);
    }
    a = Mul(a, a);
    p >>= 1;
  }

  return res;
}

template <typename T>
vector<vector<T>> Mul(vector<vector<T>>& a, vector<vector<T>>& b) {
  assert(a[0].size() == b.size());
  int n = a.size(), m = a[0].size(), w = b[0].size();
  vector<vector<T>> res(n, vector<T>(w));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < w; j++)
      for (int k = 0; k < m; k++) res[i][j] += a[i][k] * b[k][j];
  return res;
}
