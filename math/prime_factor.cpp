#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

// ===============================
// 获取整数 x 的所有质因数分解（包含重复因子）
// ===============================
//
// 算法思想：
//   使用试除法依次判断质数因子，
//   每找到一个质因子就不断除掉，直到不能整除为止。
//
// 时间复杂度：
//   - 最坏情况 O(√n)，当 x 为大质数时，需要除到 sqrt(x)。
//   - 平均情况 O(log n)，因为每次找到一个小质因子都会将 x 快速缩小。
//
// 返回结果：
//   - 一个按升序排列的向量，包含 x 的所有质因子（允许重复）。
//   - 例如：GetPrimeFactors(60) = {2, 2, 3, 5}
template <typename T>
vector<T> GetPrimeFactors(T x) {
  vector<T> fact;
  for (T i = 2; i * i <= x; i++) {
    while (x % i == 0) {
      fact.push_back(i);
      x /= i;
    }
  }
  if (x > 1) {
    fact.push_back(x);
  }
  return fact;
}

// ===============================
// 线性筛预处理最小质因子 (Min Prime Factor, SPF)
// ===============================
//
// 算法思想：
//   使用线性筛法在 [2, N] 内预计算每个整数的最小质因子 mp[i]。
//   - 如果 mp[i] == i，则说明 i 是质数。
//   - 对于合数，mp[i] 是它的最小质因子。
//   在此过程中，顺便收集所有质数到 primes 向量中。
//
// 预处理复杂度：O(N)，空间复杂度 O(N)。
//
// 应用场景：
//   有了 mp 数组后，可以在 O(log n) 的复杂度下完成任意整数 n 的质因数分解。
//
// 示例：
//   N = 20, mp[18] = 2, mp[15] = 3, mp[17] = 17
//   表示 18 的最小质因子是 2，15 的最小质因子是 3，17 本身是质数。
const int N = 1e7;
int mp[N + 1];       // mp[x] 表示 x 的最小质因子 (Smallest Prime Factor)
vector<int> primes;  // 保存筛出的所有质数

void PreCalc() {
  for (int i = 2; i <= N; i++) {
    if (mp[i] == 0) {
      mp[i] = i;
      primes.push_back(i);
    }
    for (auto p : primes) {
      if (i * p > N) break;
      mp[i * p] = p;
      if (i % p == 0) break;
    }
  }
}

// =================================
// 使用最小质因子分解整数
// =================================
//
// 输入：正整数 x (x <= N)
// 输出：x 的所有不同质因子（去重后）
//
// 算法：
//   - 每次通过 mp[x] 得到最小质因子，
//   - 连续除掉相同质因子，只保留一个。
//   - 复杂度等于质因子的个数，约 O(log n)。
//
// 示例：
//   GetPrimeFactors(60) = {2, 3, 5}
vector<int> GetPrimeFactors(int x) {
  vector<int> facts;
  while (x > 1) {
    if (facts.empty() || facts.back() != mp[x]) {
      facts.push_back(mp[x]);
    }
    x /= mp[x];
  }
  return facts;
}

// -----------------------

i64 mul(i64 a, i64 b, i64 m) {
  return static_cast<__int128>(a) * b % m;
}
i64 power(i64 a, i64 b, i64 m) {
  i64 res = 1 % m;
  for (; b; b >>= 1, a = mul(a, a, m))
    if (b & 1)
      res = mul(res, a, m);
  return res;
}
bool isprime(i64 n) {
  if (n < 2)
    return false;
  static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  int s = __builtin_ctzll(n - 1);
  i64 d = (n - 1) >> s;
  for (auto a : A) {
    if (a == n)
      return true;
    i64 x = power(a, d, n);
    if (x == 1 || x == n - 1)
      continue;
    bool ok = false;
    for (int i = 0; i < s - 1; ++i) {
      x = mul(x, x, n);
      if (x == n - 1) {
        ok = true;
        break;
      }
    }
    if (!ok)
      return false;
  }
  return true;
}

// 获得n的质因式分解
std::vector<i64> factorize(i64 n) {
  std::vector<i64> p;
  std::function<void(i64)> f = [&](i64 n) {
    if (n <= 10000) {
      for (int i = 2; i * i <= n; ++i)
        for (; n % i == 0; n /= i)
          p.push_back(i);
      if (n > 1)
        p.push_back(n);
      return;
    }
    if (isprime(n)) {
      p.push_back(n);
      return;
    }
    auto g = [&](i64 x) {
      return (mul(x, x, n) + 1) % n;
    };
    i64 x0 = 2;
    while (true) {
      i64 x = x0;
      i64 y = x0;
      i64 d = 1;
      i64 power = 1, lam = 0;
      i64 v = 1;
      while (d == 1) {
        y = g(y);
        ++lam;
        v = mul(v, std::abs(x - y), n);
        if (lam % 127 == 0) {
          d = std::gcd(v, n);
          v = 1;
        }
        if (power == lam) {
          x = y;
          power *= 2;
          lam = 0;
          d = std::gcd(v, n);
          v = 1;
        }
      }
      if (d != n) {
        f(d);
        f(n / d);
        return;
      }
      ++x0;
    }
  };
  f(n);
  std::sort(p.begin(), p.end());
  return p;
}
