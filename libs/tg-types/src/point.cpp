#include <tg-types/point.hpp>

#include <tuple>
#include <cmath>

namespace tg {

point::point() noexcept : x(0), y(0) {}

point::point(const float x, const float y) noexcept : x(x), y(y) {}

point::point(const point& o) noexcept : x(o.x), y(o.y) {}

float point::crossp(const point& p) const noexcept {
    return x * p.y - y * p.x;
}

float point::dotp(const point& p) const noexcept {
    return x * p.x + y * p.y;
}

float point::sqmag() const noexcept {
    return x*x + y*y;
}

float point::mag() const noexcept {
    return sqrt(sqmag());
}

float point::arg() const noexcept {
    return atan2(y, x);
}

point point::norm() const noexcept {
    return (*this) / mag();
}

point& point::operator+=(const point& o) noexcept {
    x += o.x;
    y += o.y;
    return *this;
}

point& point::operator-=(const point& o) noexcept {
    x -= o.x;
    y -= o.y;
    return *this;
}

point& point::operator*=(const float f) noexcept {
    x *= f;
    y *= f;
    return *this;
}

point& point::operator/=(const float f) noexcept {
    x /= f;
    y /= f;
    return *this;
}

float point::crossp(const point& a, const point& b) noexcept {
    return a.crossp(b);
}

float point::dotp(const point& a, const point& b) noexcept {
    return a.dotp(b);
}

bool operator<(const point& a, const point& b) noexcept {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

bool operator==(const point& a, const point& b) noexcept {
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const point& a, const point& b) noexcept { return !(a == b); }

point operator+(point a, const point& b) noexcept { return a += b; }
point operator-(const point& a) noexcept { return point(-a.x, -a.y); }
point operator-(point a, const point& b) noexcept { return a -= b; }
point operator*(point p, const float f) noexcept { return p *= f; }
point operator*(const float f, point p) noexcept { return p *= f; }
point operator/(point p, const float f) noexcept { return point(p.x / f, p.y / f); }

std::ostream& operator<<(std::ostream& out, const point& p) {
    return out << "(" << p.x << ", " << p.y << ")";
}

} // namespace tg
