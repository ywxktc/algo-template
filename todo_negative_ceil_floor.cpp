auto floor_div = [](i64 x, i64 y) {
  assert(y != 0);
  if (x % y != 0 && (x > 0) * (y > 0) == 0) {
    return x / y - 1;
  }
  return x / y;
};

auto ceil_div = [](i64 x, i64 y) {
  assert(y != 0);
  if (x != 0 && y != 0 && (x > 0) * (y > 0) == 0) {
    return x / y;
  }
  return (x + y - 1) / y;
};
