// 计算字符串 s 的 Z 函数（Z-array）
// Z[i] 表示 s[i..n-1] 与 s[0..n-1] 的最长公共前缀长度
// 时间复杂度为 O(n)
vector<int> Z(string s) {
  int n = s.size();
  vector<int> z(n); // z 数组，z[i] 表示 s[i..] 与 s[0..] 的最长公共前缀长度
  z[0] = n;         // z[0] 是整个字符串本身的长度

  // j 是当前 Z-box 的左端点（Z-box 是当前已知的最长匹配区间）
  for (int i = 1, j = 1; i < n; i++) {
    // 如果 i 落在当前 Z-box 内部，可以用之前的结果加速
    // z[i - j] 是之前计算的偏移结果，i - j 是对齐后在 z 数组中的相对位置
    // j + z[j] 是当前 Z-box 的右端点
    z[i] = max(0, min(j + z[j] - i, z[i - j]));

    // 尝试暴力扩展 z[i]，匹配 s[0..] 与 s[i..]
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }

    // 如果新匹配超过了当前 Z-box，更新 Z-box 的起点 j
    if (i + z[i] > j + z[j]) {
      j = i;
    }
  }
  return z;
}
