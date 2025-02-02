struct ExistCounter {
  vector<int> cnt;
  int sum = 0;

  ExistCounter(int n) : cnt(vector<int>(n, 0)), sum(0) {}

  void Add(int v) {
    if (cnt[v] == 0) {
      sum++;
    }
    cnt[v]++;
  }

  void Remove(int v) {
    assert(cnt[v] > 0 && sum > 0);
    cnt[v]--;
    if (cnt[v] == 0) {
      sum--;
    }
  }

  int Sum() {
    return sum;
  }
};