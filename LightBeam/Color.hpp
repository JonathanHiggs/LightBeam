#pragma once


#include "Bitmap.hpp"
#include "Utils.hpp"
#include "Vec3.hpp"


namespace LightBeam
{
	namespace Image
	{
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

			Color(const Math::Vec3& v)
				: _r{ v.x() }
				, _g{ v.y() }
				, _b{ v.z() }
			{}

			static const Color WHITE;
			static const Color BLACK;
			static const Color RED;
			static const Color GREEN;
			static const Color BLUE;


			double red() const noexcept { return _r; }
			double green() const noexcept { return _g; }
			double blue() const noexcept { return _b; }


			friend Color operator * (double t, const Color& c);
			friend Color operator * (const Color& c, double t);
			friend Color operator + (const Color& b, const Color& c);
			friend Color operator * (const Color& v, const Color& c);

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
				// sqrt as gamma correction
				return rgb_t{
					static_cast<unsigned char>(255.999 * Util::clamp(std::sqrt(_r), 0.0, 0.999)),
					static_cast<unsigned char>(255.999 * Util::clamp(std::sqrt(_g), 0.0, 0.999)),
					static_cast<unsigned char>(255.999 * Util::clamp(std::sqrt(_b), 0.0, 0.999)) };
			}

			static Color from_norm_vec(const Math::Vec3& v) {
				if (abs(1.0 - v.length()) > 1e-10)
					from_norm_vec(v.norm());

				return Color(0.5 * (v + Math::Vec3::one));
			}
		};


		inline Color operator *(double t, const Color& c) {
			return Color(t * c._r, t * c._g, t * c._b);
		}

		inline Color operator *(const Color& c, double t) {
			return Color(t * c._r, t * c._g, t * c._b);
		}

		inline Color operator + (const Color& b, const Color& c) {
			return Color(b._r + c._r, b._g + c._g, b._b + c._b);
		}

		inline Color operator*(const Color& u, const Color& c) {
			return Color(u._r * c._r, u._g * c._g, u._b * c._b);
		}
	}
}