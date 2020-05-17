#include "XYRectangle.hpp"
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

		XYRectangle::XYRectangle(
			double x0,
			double x1,
			double y0,
			double y1,
			double z,
			std::shared_ptr<const IMaterial> material
		)
			: _x0{ ffmin(x0, x1) }
			, _x1{ ffmax(x0, x1) }
			, _y0{ ffmin(y0, y1) }
			, _y1{ ffmax(y0, y1) }
			, _z{ z }
			, _material{ std::move(material) }
		{}

		bool XYRectangle::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			auto distance = (_z - ray.origin().z()) / ray.direction().z();

			if (distance < min_distance || distance > max_distance)
				return false;

			auto x = ray.origin().x() + distance * ray.direction().x();
			auto y = ray.origin().y() + distance * ray.direction().y();

			if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
				return false;

			auto point = Vec3(x, y, _z);
			auto outward_normal = Vec3::unit_z;
			auto uv = Vec2(
				(x - _x0) / (_x1 - _x0),
				(y - _y0) / (_y1 - _y0));

			auto front_face = Vec3::dot(ray.direction(), outward_normal) < 0.0;
			auto normal = front_face ? outward_normal : -outward_normal;

			record = HitRecord(distance, point, normal, uv, front_face, _material);

			return true;
		}

		bool XYRectangle::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = AxisAlignedBoundingBox(
				Vec3(_x0, _y0, _z - 1e-4),
				Vec3(_x1, _y1, _z + 1e-4));

			return true;
		}

		double XYRectangle::pdf_value(
			const Vec3& origin,
			const Vec3& direction) const
		{
			HitRecord hit_record;
			auto ray = Ray(origin, direction);

			if (!hit(ray, 1e-8, infinity, hit_record))
				return 0;

			auto area = (_x1 - _x0) * (_y1 - _y0);

			auto distance_squared =
				hit_record.distance()
				* hit_record.distance()
				* direction.length_squared();

			auto cosine =
				std::abs(Vec3::dot(direction, hit_record.normal()) / direction.length());

			return distance_squared / (cosine * area);
		}

		Vec3 XYRectangle::random_from_source(const Vec3& source) const
		{
			auto random_point = Vec3(
				random_double(_x0, _x1),
				random_double(_y0, _y1),
				_z);

			return random_point - source;
		}

	}
}