#include "vec3.hpp"


const Vec3 Vec3::nan = Vec3(std::nan("1"), std::nan("1"), std::nan("1"));
const Vec3 Vec3::one = Vec3(1, 1, 1);
const Vec3 Vec3::zero = Vec3(0, 0, 0);
const Vec3 Vec3::unit_x = Vec3(1, 0, 0);
const Vec3 Vec3::unit_y = Vec3(0, 1, 0);
const Vec3 Vec3::unit_z = Vec3(0, 0, 1);


std::ostream& operator<< (std::ostream& out, const Vec3& v) {
	return out << v._data[0] << ' ' << v._data[1] << ' ' << v._data[2];
}

Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u._data[0] + v._data[0], u._data[1] + v._data[1], u._data[2] + v._data[2]);
}

Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u._data[0] - v._data[0], u._data[1] - v._data[1], u._data[2] - v._data[2]);
}

Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u._data[0] * v._data[0], u._data[1] * v._data[1], u._data[2] * v._data[2]);
}

Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v._data[0], t * v._data[1], t * v._data[2]);
}

Vec3 operator*(const Vec3& v, double t) {
	return Vec3(t * v._data[0], t * v._data[1], t * v._data[2]);
}

Vec3 operator/(const Vec3& v, double t) {
	return Vec3(v._data[0] / t, v._data[1] / t, v._data[2] / t);
}