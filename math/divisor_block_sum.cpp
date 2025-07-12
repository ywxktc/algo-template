// 定义 f(val) 的处理方式，可以按需修改
i64 f(i64 val) {
  return val; // 举例：f(val) = val，即计算 ∑ floor(n / i)
}

// 主函数：处理 ∑_{i=1}^n f(n / i)
i64 divisor_block_sum(i64 n) {
  i64 res = 0;
  for (i64 l = 1, r; l <= n; l = r + 1) {
    i64 val = n / l;             // 当前区间内 floor(n / i) 的值
    r = n / val;                 // 找到该值连续出现的最大右端点
    res += (r - l + 1) * f(val); // 区间内值相同，可以直接乘
  }
  return res;
}