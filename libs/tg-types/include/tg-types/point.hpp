#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>

namespace tg {

struct point {
    float x;
    float y;

    point() noexcept;
    point(const float x, const float y) noexcept;
    point(const point& o) noexcept;

    float crossp(const point& p) const noexcept;
    float dotp(const point& p) const noexcept;

    float sqmag() const noexcept;
    float mag() const noexcept;
    float arg() const noexcept;
    point norm() const noexcept;

    point& operator+=(const point& o) noexcept;
    point& operator-=(const point& o) noexcept;
    point& operator*=(const float f) noexcept;
    point& operator/=(const float f) noexcept;

    static float crossp(const point& a, const point& b) noexcept;
    static float dotp(const point& a, const point& b) noexcept;
};

bool operator<(const point& a, const point& b) noexcept;

bool operator==(const point& a, const point& b) noexcept;
bool operator!=(const point& a, const point& b) noexcept;

point operator+(point a, const point& b) noexcept;
point operator-(const point& a) noexcept;
point operator-(point a, const point& b) noexcept;
point operator*(point p, const float f) noexcept;
point operator*(const float f, point p) noexcept;
point operator/(point p, const float f) noexcept;

std::ostream& operator<<(std::ostream& out, const point& p);

} // namespace tg

#endif // POINT_HPP
