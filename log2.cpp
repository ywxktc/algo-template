int lg(long long x) {
  assert(x > 0);
  int k = 0;
  while (x > 0) {
    k++;
    x >>= 1;
  }
  return k - 1;
}
