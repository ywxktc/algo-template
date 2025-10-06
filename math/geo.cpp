
#include <bits/stdc++.h>
using namespace std;

/// @brief 二维点 / 向量模板（适用于 double / long double）
/// 常考功能：长度、叉积、点积、旋转、线段相交、点到线段距离等。
template <typename T>
struct Point {
  using P = Point;
  T x = 0, y = 0;

  Point(T x = 0, T y = 0) : x(x), y(y) {}

  // ===============================
  // 基础运算
  // ===============================

  /// @brief 向量长度平方 |v|^2
  T Norm2() const { return x * x + y * y; }

  /// @brief 向量长度 |v|
  T Norm() const { return sqrtl(Norm2()); }

  /// @brief 单位向量（长度=1）
  P Unit() const {
    T n = Norm();
    return (n == 0 ? *this : *this / n);
  }

  /// @brief 点积（内积）v·p = |v||p|cosθ
  T Dot(const P& p) const { return x * p.x + y * p.y; }

  /// @brief 叉积（有向面积）v×p = |v||p|sinθ
  T Cross(const P& p) const { return x * p.y - y * p.x; }

  // ===============================
  // 运算符重载
  // ===============================
  P operator+(const P& rhs) const { return {x + rhs.x, y + rhs.y}; }
  P operator-(const P& rhs) const { return {x - rhs.x, y - rhs.y}; }
  P operator*(T k) const { return {x * k, y * k}; }
  P operator/(T k) const { return {x / k, y / k}; }
  friend P operator*(T k, const P& p) { return {p.x * k, p.y * k}; }
  friend ostream& operator<<(ostream& os, const P& p) {
    return os << "(" << p.x << "," << p.y << ")";
  }

  // ===============================
  // 几何函数
  // ===============================

  /// @brief 极角（atan2）
  double Angle() const { return atan2(y, x); }

  /// @brief 夹角：返回与 p 的夹角（弧度）
  double AngleBetween(const P& p) const {
    return acos(Dot(p) / (Norm() * p.Norm()));
  }

  /// @brief 旋转 rad 弧度（逆时针）
  P Rot(double rad) const {
    double c = cos(rad), s = sin(rad);
    return {x * c - y * s, x * s + y * c};
  }

  /// @brief 垂直向量（逆时针旋转 90°）
  P Perp() const { return {-y, x}; }

  /// @brief 顺时针旋转 90°
  P Rot90CW() const { return {y, -x}; }

  /// @brief 逆时针旋转 90°
  P Rot90CCW() const { return {-y, x}; }

  /// @brief 两点间距离
  static double Dist(const P& a, const P& b) {
    return (a - b).Norm();
  }

  // ===============================
  // 工具函数
  // ===============================

  /// @brief 符号函数（带浮点误差判断）
  static int Sign(T x, T eps = 1e-9) {
    if (x > eps) return 1;
    if (x < -eps) return -1;
    return 0;
  }

  /// @brief 判断点是否在点集凸包的逆时针方向
  static int Orientation(const P& a, const P& b, const P& c) {
    return Sign((b - a).Cross(c - a));
  }

  // ===============================
  // 常考函数
  // ===============================

  /// @brief 判断点 p 是否在线段 ab 上（含端点）
  static bool OnSegment(const P& a, const P& b, const P& p) {
    return Sign((b - a).Cross(p - a)) == 0 &&
           Sign((p.x - a.x) * (p.x - b.x) + (p.y - a.y) * (p.y - b.y)) <= 0;
  }

  /// @brief 点到线段 ab 的最短距离
  static double DistPointSegment(const P& a, const P& b, const P& p) {
    if ((b - a).Dot(p - a) < 0) return (p - a).Norm();  // p 在 a 外
    if ((a - b).Dot(p - b) < 0) return (p - b).Norm();  // p 在 b 外
    return fabs((b - a).Cross(p - a)) / (b - a).Norm();
  }

  /// @brief 判断两线段是否相交（含端点）
  static bool SegmentIntersect(const P& a, const P& b, const P& c, const P& d) {
    int d1 = Sign((b - a).Cross(c - a));
    int d2 = Sign((b - a).Cross(d - a));
    int d3 = Sign((d - c).Cross(a - c));
    int d4 = Sign((d - c).Cross(b - c));
    if (d1 * d2 < 0 && d3 * d4 < 0) return true;  // 一般相交
    if (d1 == 0 && OnSegment(a, b, c)) return true;
    if (d2 == 0 && OnSegment(a, b, d)) return true;
    if (d3 == 0 && OnSegment(c, d, a)) return true;
    if (d4 == 0 && OnSegment(c, d, b)) return true;
    return false;
  }

  /// @brief 两线段交点（若相交）
  static optional<P> SegmentIntersection(const P& a, const P& b, const P& c, const P& d) {
    P ab = b - a, cd = d - c;
    double det = ab.Cross(cd);
    if (fabs(det) < 1e-12) return {};  // 平行或重合
    double t = (c - a).Cross(cd) / det;
    return a + ab * t;
  }

  /// @brief 多边形面积（正负表示顺/逆时针）
  static double PolygonArea(const vector<P>& v) {
    double area = 0;
    for (int i = 0, n = v.size(); i < n; i++)
      area += v[i].Cross(v[(i + 1) % n]);
    return area / 2.0;
  }
};

using P = Point<double>;

int main() {
  P a(0, 0), b(4, 0), c(2, 3);

  cout << "向量长度: " << (b - a).Norm() << "\n";
  cout << "夹角: " << a.AngleBetween(b) << "\n";
  cout << "垂直向量: " << (b - a).Perp() << "\n";
  cout << "点c到线段ab距离: " << P::DistPointSegment(a, b, c) << "\n";

  P d(2, -2), e(2, 2);
  cout << "线段相交: " << (P::SegmentIntersect(a, b, d, e) ? "Yes" : "No") << "\n";

  vector<P> poly = {{0, 0}, {4, 0}, {4, 3}, {0, 3}};
  cout << "矩形面积: " << P::PolygonArea(poly) << "\n";
}
