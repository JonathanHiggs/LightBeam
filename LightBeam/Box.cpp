#include "Box.hpp"
#include "XYRectangle.hpp"
#include "XZRectangle.hpp"
#include "YZRectangle.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Materials;
using namespace LightBeam::Rendering;


namespace LightBeam
{
	namespace Shapes
	{

		Box::Box(
			const Vec3& p0,
			const Vec3& p1,
			std::shared_ptr<const IMaterial> material
		)
			: _min{ p0 }
			, _max{ p1 }
		{
			auto sides = std::vector<std::shared_ptr<const IHittable>>();

			sides.emplace_back(std::make_shared<const XYRectangle>(
				_min.x(), _max.x(), _min.y(), _max.y(), _max.z(), material));

			sides.emplace_back(std::make_shared<const XYRectangle>(
				_min.x(), _max.x(), _min.y(), _max.y(), _min.z(), material));

			sides.emplace_back(std::make_shared<const XZRectangle>(
				_min.x(), _max.x(), _min.z(), _max.z(), _max.y(), material));

			sides.emplace_back(std::make_shared<const XZRectangle>(
				_min.x(), _max.x(), _min.z(), _max.z(), _min.y(), material));

			sides.emplace_back(std::make_shared<const YZRectangle>(
				_min.y(), _max.y(), _min.z(), _max.z(), _max.x(), material));

			sides.emplace_back(std::make_shared<const YZRectangle>(
				_min.y(), _max.y(), _min.z(), _max.z(), _min.x(), material));

			_sides = HittableList(sides);
		}

		bool Box::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			return _sides.hit(ray, min_distance, max_distance, record);
		}

		bool Box::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = AxisAlignedBoundingBox(_min, _max);
			return true;
		}

	}
}