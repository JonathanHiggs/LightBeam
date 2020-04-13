#pragma once

#include "Ray.hpp"
#include "Vec3.hpp"


namespace LightBeam
{
	namespace Rendering
	{
		class AxisAlignedBoundingBox {
		private:
			Math::Vec3 _min;
			Math::Vec3 _max;

		public:
			AxisAlignedBoundingBox();
			AxisAlignedBoundingBox(const Math::Vec3& min, const Math::Vec3& max);

			const Math::Vec3& min() const noexcept { return _min; }
			const Math::Vec3& max() const noexcept { return _max; }

			bool hit(const Ray& ray, double min_distance, double max_distance) const;

			static AxisAlignedBoundingBox surrounding_box(
				const AxisAlignedBoundingBox& box0,
				const AxisAlignedBoundingBox& box1);
		};
	}
}