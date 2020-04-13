#include "AxisAlignedBoundingBox.hpp"
#include "utils.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Rendering
	{
		AxisAlignedBoundingBox::AxisAlignedBoundingBox()
			: _min{ Vec3::zero }
			, _max{ Vec3::zero }
		{}

		AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vec3& min, const Vec3& max)
			: _min{ min }
			, _max{ max }
		{}


		bool AxisAlignedBoundingBox::hit(const Ray& ray, double min_distance, double max_distance) const
		{
			for (int axis = 0; axis < 3; axis++) {
				auto t0 = ffmin(
					(_min[axis] - ray.origin()[axis]) / ray.direction()[axis],
					(_max[axis] - ray.origin()[axis]) / ray.direction()[axis]);
				auto t1 = ffmax(
					(_min[axis] - ray.origin()[axis]) / ray.direction()[axis],
					(_max[axis] - ray.origin()[axis]) / ray.direction()[axis]);
				min_distance = ffmax(t0, min_distance);
				max_distance = ffmin(t1, max_distance);
				if (max_distance <= min_distance)
					return false;
			}
			return true;

			//for (int axis = 0; axis < 3; axis++) {
			//	// need to check for ray.direction()[axis] == 0?
			//	auto invD = 1.0 / ray.direction()[axis];
			//	auto t0 = (_min[axis] - ray.origin()[axis]) * invD;
			//	auto t1 = (_min[axis] - ray.origin()[axis]) * invD;

			//	if (invD < 0.0)
			//		std::swap(t0, t1);

			//	min_distance = t0 > min_distance ? t0 : min_distance;
			//	max_distance = t1 < min_distance ? t1 : max_distance;

			//	if (max_distance <= min_distance)
			//		return false;
			//}

			//return true;
		}

		AxisAlignedBoundingBox AxisAlignedBoundingBox::surrounding_box(
			const AxisAlignedBoundingBox& box0,
			const AxisAlignedBoundingBox& box1)
		{
			return AxisAlignedBoundingBox(
				Vec3(
					ffmin(box0._min.x(), box1._min.x()),
					ffmin(box0._min.y(), box1._min.y()),
					ffmin(box0._min.z(), box1._min.z())),
				Vec3(
					ffmax(box0._max.x(), box1._max.x()),
					ffmax(box0._max.y(), box1._max.y()),
					ffmax(box0._max.z(), box1._max.z())));
		}
	}
}