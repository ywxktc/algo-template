// 位运算

// 求有多少位bit
__builtin_popcount(7) = 3

// 前导零
__builtin_clz(6) = 29

// 最高位1所在的权重
31 - builtin_clz(x)
63 - builtin_clz(x)

// 求lowbit
template<typename T>
T lowbit(T x) {
  return x & -x;
}

// 求log2(x)向下取整
int floor_log2(long long x) {
  int ret = 0;
  while (x > 0) {
    x >>= 1;
    ret++;
  }
  return ret;
}

// 求2^x, x>=0
long long pow2(int x) {
  assert(x >= 0);
  long long res = 1;
  while (x > 0) {
    res *= 2;
    x--;
  }
  return res;
}

bit_width(unsigned())
bit_floor(unsigned())