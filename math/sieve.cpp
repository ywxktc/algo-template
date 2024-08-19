// 埃拉托斯特尼筛法
// O(nlglg(n))
// is_prime[x] = x 是否是素数
// primes保存[1,n]中所有素数
// ref: https://oi-wiki.org/math/number-theory/sieve/
pair<vector<bool>, vector<int>> Eratosthenes(int n) {
  vector<int> is_prime(n + 1, true);
  vector<int> primes;
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
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

// 执行线性筛，返回[1,n]中的质数
// is_prime[x] = x是否是素数
// primes保存[1,n]中所有素数
// ref: https://www.bilibili.com/video/BV1Ah411N7E4/?spm_id_from=333.337.search-card.all.click&vd_source=dee7adb2d732cdff52d8b3fda8962e30
pair<vector<bool>, vector<int>> RunLinerSieve(int n) {
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
      if (i % p == 0) {
        break;
      }
    }
  }
  return {is_prime, primes};
}
