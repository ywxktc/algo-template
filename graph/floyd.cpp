#include "bits/stdc++.h"
#include <vector>
using namespace std;

int main() {
  int n = 10;
  vector f(n, vector<int>(n));
  for (int k = 0; k < n; k++) {
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < n; y++) {
        f[x][y] = min(f[x][y], f[x][k] + f[k][y]);
      }
    }
  }

  // if add road u->v
  int u, v, c;
  cin >> u >> v >> c;
  f[u][v] = min(f[u][v], c);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      f[x][y] = min({
          f[x][y],
          f[x][u] + f[u][v] + f[v][y],
      });
    }
  }
}