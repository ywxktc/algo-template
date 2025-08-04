// 在区间 [l, r) 中找到第一个为真的索引下标
// 如果不存在，返回 r
// e.g. [1,3,77,111]
// 在区间 [0, 4) 中找到第一个大于等于 50 的位置, 函数返回 2
// 在区间 [0, 4) 中找到第一个大于等于 120 的位置, 函数返回 4 (不存在)
int BinarySearch(int l, int r, auto &&Check) {
  while (l < r) {
    int m = l + (r - l) / 2;
    if (Check(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return l;
}