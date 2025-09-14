#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Binom {
 private:
  vector<T> fact;
  vector<T> inv_fact;

  void adaptive(int m) {
    for (int i = fact.size(); i <= m; i++) {
      fact.push_back(i == 0 ? T(1) : T(i) * fact[i - 1]);
      inv_fact.push_back(1 / fact.back());
    }
  }

 public:
  T operator()(int m, int n) {
    assert(m >= n);
    adaptive(m);
    return fact[m] * inv_fact[n] * inv_fact[m - n];
  }
};

Binom<int> C;
