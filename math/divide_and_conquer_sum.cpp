// 假设我们要求 f(n) = ∑(n / i) for i = 1 to n
ll divide_and_conquer_sum(ll n) {
    ll result = 0;
    for (ll i = 1; i <= n; ) {
        ll div = n / i; // 商值
        ll next_i = n / div + 1; // 下一段起点
        result += div * (next_i - i); // 累加整段值
        i = next_i; // 更新区间起点
    }
    return result;
}
