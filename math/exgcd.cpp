template <typename T>
T exgcd(T a, T b, T &x, T &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T g = exgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return g;
}

// 通解
// x = x0 + (b/g)n
// y = y0 - (a/g)n

// 当且仅当 g|c, 存在 ax+by=c