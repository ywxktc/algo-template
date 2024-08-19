// calculate base^p
long long qpow(long long x, int p) {
  long long ret = 1, base = x;
  while (p > 0) {
    if (p & 1) {
      ret *= base;
    }
    base *= base;
    p >>= 1;
  }
  return ret;
}
