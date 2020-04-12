#pragma once


#include "bitmap.hpp"
#include "vec3.hpp"
#include "utils.hpp"


class Color {
private:
	double _r;
	double _g;
	double _b;

public:
	Color()
		: _r{ 0 }, _g{ 0 }, _b{ 0 }
	{}

	Color(double r, double g, double b)
		: _r{ r }, _g{ g }, _b{ b }
	{}

	Color(const Vec3& v)
		: _r{ v.x() }
		, _g{ v.y() }
		, _b{ v.z() }
	{}

	static const Color white;
	static const Color black;


	double red() const noexcept { return _r; }
	double green() const noexcept { return _g; }
	double blue() const noexcept { return _b; }


	Color& operator+=(const Color& c) {
		_r += c._r;
		_g += c._g;
		_b += c._b;
		return *this;
	}

	Color& operator/=(double scale) {
		_r /= scale;
		_g /= scale;
		_b /= scale;
		return *this;
	}

	rgb_t to_rgb() const {
		// Make sure to clamp to range 0.0 - 1.0 before converting up
		return rgb_t{
			static_cast<unsigned char>(255.999 * clamp(_r, 0.0, 0.999)),
			static_cast<unsigned char>(255.999 * clamp(_g, 0.0, 0.999)),
			static_cast<unsigned char>(255.999 * clamp(_b, 0.0, 0.999)) };
	}

	static Color from_norm_vec(const Vec3& v) {
		if (abs(1.0 - v.length()) > 1e-10)
			from_norm_vec(v.norm());

		return Color(0.5 * (v + Vec3::one));
	}
};

