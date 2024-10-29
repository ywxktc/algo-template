struct Trie {
  struct Node {
    int cnt;
    array<int, 26> next;
    Node() : cnt(0), next{} {}
  };

  vector<Node> nodes;
  Trie() { nodes.emplace_back(); }

  // Inserts a string into the Trie
  void Insert(const string &s) {
    int u = 0;
    for (char c : s) {
      int idx = c - 'a';
      if (!nodes[u].next[idx]) {
        nodes[u].next[idx] = nodes.size();
        nodes.emplace_back();
      }
      u = nodes[u].next[idx];
      nodes[u].cnt++;
    }
  }
  
  // Searches the Trie for the existence of a specified string
  bool Search(const string &s) const {
    int u = 0;
    for (char c : s) {
      int idx = c - 'a';
      if (!nodes[u].next[idx]) {
        return false;
      }
      u = nodes[u].next[idx];
    }
    return nodes[u].cnt > 0;
  }
};
