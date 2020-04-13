#pragma once


#include <iostream>

#include "Random.hpp"


class Vec2 {
private:
	double _data[2];

public:
	Vec2() : _data{ 0.0, 0.0 }
	{}

	Vec2(double x, double y)
		: _data{ x, y }
	{}

	static const Vec2 nan;
	static const Vec2 one;
	static const Vec2 zero;
	static const Vec2 unit_x;
	static const Vec2 unit_y;


	double x() const noexcept { return _data[0]; }
	double y() const noexcept { return _data[1]; }


	Vec2 operator -() const { return Vec2(-_data[0], -_data[1]); }


	inline double length() const {
		return std::sqrt(length_squared());
	}

	inline double length_squared() const {
		return _data[0] * _data[0] + _data[1] * _data[1];
	}

	friend std::ostream& operator <<(std::ostream& os, const Vec2& v);
	friend Vec2 operator+(const Vec2& u, const Vec2& v);
	friend Vec2 operator-(const Vec2& u, const Vec2& v);
	friend Vec2 operator*(const Vec2& u, const Vec2& v);
	friend Vec2 operator*(double t, const Vec2& v);
	friend Vec2 operator*(const Vec2& u, double t);
	friend Vec2 operator/(const Vec2& u, double t);

	static double dot(const Vec2& u, const Vec2& v) {
		return u._data[0] * v._data[0]
			+ u._data[1] * v._data[1];
	}

	static Vec2 interpolate(const Vec2& u, const Vec2& v, double t) {
		return (1.0 - t) * u + t * v;
	}

	static Vec2 random_in_unit_disk() {
		while (true) {
			const auto p = Vec2(random_double(-1, 1), random_double(-1, 1));
			if (p.length_squared() >= 1) continue;
			return p;
		}
	}
};