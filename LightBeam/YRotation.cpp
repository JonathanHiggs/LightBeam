#include "YRotation.hpp"
#include "utils.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Rendering;
using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Shapes
	{

		YRotation::YRotation(
			double angle,
			std::shared_ptr<const Rendering::IHittable> hittable
		)
			: _hittable{ std::move(hittable) }
			, _sin_theta{ std::sin(degrees_to_radians(angle)) }
			, _cos_theta{ std::cos(degrees_to_radians(angle)) }
		{
			_has_box = _hittable->bounding_box(0, 1, _bounding_box);

			auto min = Vec3::positive_infinity;
			auto max = Vec3::negative_infinity;

			for (auto i = 0; i < 2; i++)
			{
				for (auto j = 0; j < 2; j++)
				{
					for (auto k = 0; k < 2; k++)
					{
						auto x = i * _bounding_box.max().x() + (1.0 - i) * _bounding_box.min().x();
						auto y = j * _bounding_box.max().y() + (1.0 - j) * _bounding_box.min().y();
						auto z = k * _bounding_box.max().z() + (1.0 - k) * _bounding_box.min().z();

						auto new_x = _cos_theta * x + _sin_theta * z;
						auto new_z = -_sin_theta * x + _cos_theta * z;

						min = Vec3(
							ffmin(min.x(), new_x),
							ffmin(min.y(), y),
							ffmin(min.z(), new_z));

						max = Vec3(
							ffmax(max.x(), new_x),
							ffmax(max.y(), y),
							ffmax(max.z(), new_z));
					}
				}
			}

			_bounding_box = AxisAlignedBoundingBox(min, max);
		}

		bool YRotation::hit(
			const Rendering::Ray& ray,
			double min_distance,
			double max_distance,
			Rendering::HitRecord& record) const
		{
			auto origin = Vec3(
				_cos_theta * ray.origin().x() - _sin_theta * ray.origin().z(),
				ray.origin().y(),
				_sin_theta * ray.origin().x() + _cos_theta * ray.origin().z());

			auto direction = Vec3(
				_cos_theta * ray.direction().x() - _sin_theta * ray.direction().z(),
				ray.direction().y(),
				_sin_theta * ray.direction().x() + _cos_theta * ray.direction().z());

			auto rotated_ray = Ray(origin, direction, ray.time());

			if (!_hittable->hit(rotated_ray, min_distance, max_distance, record))
				return false;

			auto point = Vec3(
				_cos_theta * record.point().x() + _sin_theta * record.point().z(),
				record.point().y(),
				-_sin_theta * record.point().x() + _cos_theta * record.point().z());

			auto normal = Vec3(
				_cos_theta * record.normal().x() + _sin_theta * record.normal().z(),
				record.normal().y(),
				-_sin_theta * record.normal().x() + _cos_theta * record.normal().z());

			record = HitRecord(
				record.distance(),
				point,
				normal,
				record.uv(),
				record.front_face(),
				record.meterial());

			return true;
		}

		bool YRotation::bounding_box(
			double begin_time,
			double end_time,
			Rendering::AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = _bounding_box;
			return _has_box;
		}

	}
}