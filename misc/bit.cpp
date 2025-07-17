#pragma once
#include <bit> // ✅ C++20 位运算函数
#include <bits/stdc++.h>
using namespace std;

// ============================
// 🧠 位运算工具（C++20 标准）
// ============================

// ✅ 返回 2^x，x ≥ 0
constexpr int64_t pow2(int x) {
  return 1LL << x;
}

// ✅ 返回最低位的 1（lowbit）
template <typename T>
constexpr T lowbit(T x) {
  return x & -x;
}

// ✅ 返回二进制中 1 的个数
template <typename T>
constexpr int popcount(T x) {
  return std::popcount(x);
  // return __builtin_popcountll(x); // ← 可选：GCC/Clang 内建版本
}

// ✅ 返回 x 所需的 bit 位数（即 bit_width）
// e.g. x = 12 (1100) → 4
template <typename T>
constexpr int bit_width(T x) {
  return std::bit_width(x);
}

// ✅ 返回 floor(log2(x))
// e.g. x = 12 → 3
template <typename T>
constexpr int lg(T x) {
  return bit_width(x) - 1;
}

// ✅ 返回最大不超过 x 的 2 的幂（bit_floor）
// e.g. x = 12 → 8
template <typename T>
constexpr T bit_floor(T x) {
  return std::bit_floor(x);
}

// ✅ 返回最小不小于 x 的 2 的幂（bit_ceil）
// e.g. x = 12 → 16
template <typename T>
constexpr T bit_ceil(T x) {
  return std::bit_ceil(x);
}

// ✅ 返回前导零数量（leading zero count）
// e.g. 0000...1100 → 28
template <typename T>
constexpr int leading_zeros(T x) {
  return std::countl_zero(x);
  // return __builtin_clzll(x); // ← 可选 fallback
}

// ✅ 返回末尾零数量（trailing zero count）
// e.g. 0000...1000 → 3
template <typename T>
constexpr int trailing_zeros(T x) {
  return std::countr_zero(x);
  // return __builtin_ctzll(x); // ← 可选 fallback
}