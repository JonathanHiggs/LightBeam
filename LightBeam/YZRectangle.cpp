#include "YZRectangle.hpp"
#include "utils.hpp"
#include "Constants.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Materials;
using namespace LightBeam::Rendering;
using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Shapes
	{

		YZRectangle::YZRectangle(
			double y0,
			double y1,
			double z0,
			double z1,
			double x,
			std::shared_ptr<const IMaterial> material
		)
			: _y0{ ffmin(y0, y1) }
			, _y1{ ffmax(y0, y1) }
			, _z0{ ffmin(z0, z1) }
			, _z1{ ffmax(z0, z1) }
			, _x{ x }
			, _material{ std::move(material) }
		{}

		bool YZRectangle::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			auto distance = (_x - ray.origin().x()) / ray.direction().x();

			if (distance < min_distance || distance > max_distance)
				return false;

			auto y = ray.origin().y() + distance * ray.direction().y();
			auto z = ray.origin().z() + distance * ray.direction().z();

			if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
				return false;

			auto point = Vec3(_x, y, z);
			auto outward_normal = Vec3::unit_x;
			auto uv = Vec2(
				(y - _y0) / (_y1 - _y0),
				(z - _z0) / (_z1 - _z0));

			auto front_face = Vec3::dot(ray.direction(), outward_normal) < 0.0;
			auto normal = front_face ? outward_normal : -outward_normal;

			record = HitRecord(distance, point, normal, uv, front_face, _material);

			return true;
		}

		bool YZRectangle::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = AxisAlignedBoundingBox(
				Vec3(_x - 1e-4, _y0, _z0),
				Vec3(_x + 1e-4, _y1, _z1));

			return true;
		}

		double YZRectangle::pdf_value(
			const Vec3& origin,
			const Vec3& direction) const
		{
			HitRecord hit_record;
			auto ray = Ray(origin, direction);

			if (!hit(ray, 1e-8, infinity, hit_record))
				return 0;

			auto area = (_y1 - _y0) * (_z1 - _z0);

			auto distance_squared =
				hit_record.distance()
				* hit_record.distance()
				* direction.length_squared();

			auto cosine =
				std::abs(Vec3::dot(direction, hit_record.normal()) / direction.length());

			return distance_squared / (cosine * area);
		}

		Vec3 YZRectangle::random_from_source(const Vec3& source) const
		{
			auto random_point = Vec3(
				_x,
				random_double(_y0, _y1),
				random_double(_z0, _z1));

			return random_point - source;
		}

	}
}