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
T lowbit(T x) { return x & -x; }

// 求2^x, x>=0
i64 pow2(int x) { return (1LL << x); }

// 计算存储x需要多少位bit,等价于 1 + floor(log2(x))
// 例如x=12(1100)，返回4
bit_width<u64>(x)

// 计算最大的y，使得2^y<=x
// 例如x=12(1100), 返回8
bit_floor<u64>(x)

// 返回floor(log2(x))
// 例如 12(1100) 返回 3
int lg(u64 x) { return bit_width<u64>(x) - 1; }

// 返回1的数量,
// 例如12(1100)返回2
popcount<u64>(x);

// c++20后的bit函数
// ref: https://learn.microsoft.com/zh-cn/cpp/standard-library/bit-functions?view=msvc-170