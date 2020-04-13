#pragma once

#include "Vec3.hpp"


namespace LightBeam
{
	namespace Rendering
	{
		class Ray {
		private:
			Math::Vec3 _origin;
			Math::Vec3 _direction;
			double _time;


		public:
			Ray()
				: _origin{ Math::Vec3::nan }
				, _direction{ Math::Vec3::nan }
				, _time{ std::nan("1") }
			{}

			Ray(const Math::Vec3& origin, const Math::Vec3& direction, double time = 0.0)
				: _origin{ origin }
				, _direction{ direction }
				, _time{ time }
			{}


			const Math::Vec3& origin() const noexcept { return _origin; }
			const Math::Vec3& direction() const noexcept { return _direction; }
			double time() const noexcept { return _time;  }


			Math::Vec3 at(double t) const {
				return _origin + t * _direction;
			}
		};
	}
}