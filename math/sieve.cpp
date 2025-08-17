#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 埃拉托斯特尼筛法 (Sieve of Eratosthenes)
 *
 * @param n 筛到的最大范围
 * @return {is_prime, primes}
 *   - is_prime[x] = x 是否是素数
 *   - primes = [1, n] 内所有质数
 *
 * @complexity O(n log log n)
 * @ref https://oi-wiki.org/math/number-theory/sieve/
 */
pair<vector<bool>, vector<int>> Eratosthenes(int n) {
  vector<bool> is_prime(n + 1, true);
  vector<int> primes;
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      // 优化：从 i*i 开始标记，因为比 i 小的倍数之前已被更小的质数筛掉
      if (1LL * i * i > n) {
        continue;
      }
      for (int j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
  return {is_prime, primes};
}

/**
 * @brief 线性筛法 (Linear Sieve)
 *
 * @param n 筛到的最大范围
 * @return {is_prime, primes}
 *   - is_prime[x] = x 是否是素数
 *   - primes = [1, n] 内所有质数
 *
 * @complexity O(n)
 *   每个合数只会被其最小质因子筛掉一次
 * @ref https://www.bilibili.com/video/BV1Ah411N7E4
 */
pair<vector<bool>, vector<int>> LinearSieve(int n) {
  vector<bool> is_prime(n + 1, true);
  vector<int> primes;
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (auto p : primes) {
      if (1LL * i * p > n) {
        break;
      }
      is_prime[i * p] = false;
      // 保证每个合数只被最小质因子筛一次
      if (i % p == 0) {
        break;
      }
    }
  }
  return {is_prime, primes};
}
