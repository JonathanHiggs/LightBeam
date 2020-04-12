#include "vec2.hpp"


const Vec2 Vec2::nan = Vec2(std::nan("1"), std::nan("1"));
const Vec2 Vec2::one = Vec2(1, 1);
const Vec2 Vec2::zero = Vec2(0, 0);
const Vec2 Vec2::unit_x = Vec2(1, 0);
const Vec2 Vec2::unit_y = Vec2(0, 1);


std::ostream& operator <<(std::ostream& os, const Vec2& v) {
	return os << v._data[0] << ' ' << v._data[1];
}

Vec2 operator+(const Vec2& u, const Vec2& v) {
	return Vec2(u._data[0] + v._data[0], u._data[1] + v._data[0]);
}

Vec2 operator-(const Vec2& u, const Vec2& v) {
	return Vec2(u._data[0] - v._data[0], u._data[1] - v._data[0]);
}

Vec2 operator*(const Vec2& u, const Vec2& v) {
	return Vec2(u._data[0] * v._data[0], u._data[1] * v._data[0]);
}

Vec2 operator*(double t, const Vec2& v) {
	return Vec2(t * v._data[0], t * v._data[0]);
}

Vec2 operator*(const Vec2& u, double t) {
	return Vec2(u._data[0] * t, u._data[1] * t);
}

Vec2 operator/(const Vec2& u, double t) {
	return Vec2(u._data[0] / t, u._data[1] / t);
}