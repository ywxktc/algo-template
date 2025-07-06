#ifndef DEBUG_TEMPLATE_CPP
#define DEBUG_TEMPLATE_CPP

#include <bits/stdc++.h>

namespace debug_util {

using std::cerr;
using std::endl;
using std::string;

template <typename T>
concept Iterable = requires(T &&x) {
  std::begin(x);
} && !std::is_same_v<std::remove_cvref_t<T>, string>;

inline void Print(const char *x) { cerr << x; }

inline void Print(char x) { cerr << '\'' << x << '\''; }

inline void Print(bool x) { cerr << (x ? "true" : "false"); }

inline void Print(const string &x) { cerr << '"' << x << '"'; }

inline void Print(const std::vector<bool> &v) {
  cerr << '{';
  bool first = true;
  for (bool b : v) {
    if (!first)
      cerr << ',';
    cerr << (b ? "true" : "false");
    first = false;
  }
  cerr << '}';
}

template <typename T>
void Print(const T &x);

template <typename A, typename B>
inline void Print(const std::pair<A, B> &p) {
  cerr << '(';
  Print(p.first);
  cerr << ',';
  Print(p.second);
  cerr << ')';
}

template <typename... Args>
inline void Print(const std::tuple<Args...> &t) {
  cerr << '(';
  std::apply(
      [](const auto &...args) {
        size_t n = 0;
        (..., (n++ > 0 ? (cerr << ',', Print(args)) : Print(args)));
      },
      t);
  cerr << ')';
}

template <typename T>
void Print(const T &x) {
  if constexpr (Iterable<T>) {
    cerr << '{';
    bool first = true;
    for (const auto &item : x) {
      if (!first)
        cerr << ',';
      Print(item);
      first = false;
    }
    cerr << '}';
  } else if constexpr (requires { x.top(); x.empty(); }) { // stack, priority_queue
    auto temp = x;
    cerr << '{';
    bool first = true;
    while (!temp.empty()) {
      if (!first)
        cerr << ',';
      Print(temp.top());
      temp.pop();
      first = false;
    }
    cerr << '}';
  } else if constexpr (requires { x.front(); x.empty(); }) { // queue
    auto temp = x;
    cerr << '{';
    bool first = true;
    while (!temp.empty()) {
      if (!first)
        cerr << ',';
      Print(temp.front());
      temp.pop();
      first = false;
    }
    cerr << '}';
  } else {
    cerr << x;
  }
}

template <typename T, typename... Rest>
void DebugPrinter(const char *names, T &&head, Rest &&...tail) {
  while (*names == ' ' || *names == ',')
    ++names;
  const char *end = names;
  int bracket = 0;
  while (*end && (*end != ',' || bracket > 0)) {
    if (*end == '(' || *end == '<' || *end == '{')
      ++bracket;
    if (*end == ')' || *end == '>' || *end == '}')
      --bracket;
    ++end;
  }
  cerr.write(names, end - names) << " = ";
  Print(head);
  if constexpr (sizeof...(tail)) {
    cerr << " | ";
    DebugPrinter(end, std::forward<Rest>(tail)...);
  } else {
    cerr << endl;
  }
}

} // namespace debug_util

#ifdef LOCAL
#define debug(...)               \
  std::cerr << __LINE__ << ": "; \
  debug_util::DebugPrinter(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...)
#endif

#endif // DEBUG_TEMPLATE_CPP