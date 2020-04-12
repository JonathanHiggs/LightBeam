#pragma once

#include <iostream>


class Vec3 {
private:
	double e[3];

public:
	Vec3() : e{ 0, 0, 0 }
	{}

	Vec3(double x, double y, double z)
		: e{ x, y, z }
	{}

	Vec3(const Vec3& v) noexcept
		: e{ v.e[0], v.e[1], v.e[2] }
	{}

	static const Vec3 nan;
	static const Vec3 one;
	static const Vec3 zero;
	static const Vec3 unit_x;
	static const Vec3 unit_y;
	static const Vec3 unit_z;


	double x() const noexcept { return e[0]; }
	double y() const noexcept { return e[1]; }
	double z() const noexcept { return e[2]; }


	Vec3 operator -() const { return Vec3(-e[0], -e[1], -e[2]);	}

	double operator[] (int i) { return e[1]; }


	double length() const {
		return sqrt(length_squared());
	}

	double length_squared() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	Vec3 norm() const {
		return *this / length();
	}


	friend std::ostream& operator <<(std::ostream& out, const Vec3& v);
	friend Vec3 operator+(const Vec3& u, const Vec3& v);
	friend Vec3 operator-(const Vec3& u, const Vec3& v);
	friend Vec3 operator*(const Vec3& u, const Vec3& v);
	friend Vec3 operator*(double t, const Vec3& v);
	friend Vec3 operator*(const Vec3& v, double t);
	friend Vec3 operator/(const Vec3& v, double t);
	friend double dot(const Vec3& u, const Vec3& v);
	friend Vec3 cross(const Vec3& u, const Vec3& v);

	static Vec3 interpolate(const Vec3& u, const Vec3& v, double t) {
		return (1.0 - t) * u + t * v;
	}
};


inline std::ostream& operator<< (std::ostream& out, const Vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3& v) {
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t) {
	return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator/(const Vec3& v, double t) {
	return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline double dot(const Vec3& u, const Vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(
		u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}