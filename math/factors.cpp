#include <bits/stdc++.h>
using namespace std;

// 获取计算所有因子 O(N^(1.5))
const int MAXN = 1e5;
vector<vector<int>> factors(MAXN + 1);
void PreCalc() {
  for (int x = 1; x <= MAXN; x++) {
    for (int i = 1; i * i <= x; i++) {
      if (x % i == 0) {
        factors[x].push_back(i);
        if (x / i != i) {
          factors[x].push_back(x / i);
        }
      }
    }
    sort(factors[x].begin(), factors[x].end());
  }
}
