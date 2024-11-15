template <typename T>
T exgcd(T a, T b, T &x, T &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T g = exgcd(b, a % b, y, x); // 递归调用
  y -= (a / b) * x;
  return g;
}
