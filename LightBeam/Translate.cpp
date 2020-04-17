#include "Translate.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Rendering;


namespace LightBeam
{
	namespace Shapes
	{

		Translate::Translate(
			const Vec3& offset,
			std::shared_ptr<const IHittable> hittable
		)
			: _hittable{ std::move(hittable) }
			, _offset{ offset }
		{}

		bool Translate::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			auto translated = Ray(
				ray.origin() - _offset,
				ray.direction(),
				ray.time());

			if (!_hittable->hit(translated, min_distance, max_distance, record))
				return false;

			record = HitRecord(
				record.distance(),
				record.point() + _offset,
				record.normal(),
				record.uv(),
				record.front_face(),
				record.meterial());

			return true;
		}

		bool Translate::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			if (!_hittable->bounding_box(begin_time, end_time, bounding_box))
				return false;

			bounding_box = AxisAlignedBoundingBox(
				bounding_box.min() + _offset,
				bounding_box.max() + _offset);

			return true;
		}

	}
}