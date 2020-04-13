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


		public:
			Ray()
				: _origin{ Math::Vec3::nan }
				, _direction{ Math::Vec3::nan }
			{}

			Ray(const Math::Vec3& origin, const Math::Vec3& direction)
				: _origin{ origin }
				, _direction{ direction }
			{}


			const Math::Vec3& origin() const noexcept { return _origin; }
			const Math::Vec3& direction() const noexcept { return _direction; }


			Math::Vec3 at(double t) const {
				return _origin + t * _direction;
			}
		};
	}
}