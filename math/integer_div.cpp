template <typename T>
T divceil(T a, T b) {
  return a / b + (a % b > 0);
}

template <typename T>
T divfloor(T a, T b) {
  return a / b - (a % b < 0);
}