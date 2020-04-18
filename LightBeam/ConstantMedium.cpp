#include "Constants.hpp"
#include "ConstantMedium.hpp"
#include "Isotropic.hpp"
#include "Random.hpp"


using namespace LightBeam::Materials;
using namespace LightBeam::Math;
using namespace LightBeam::Rendering;
using namespace LightBeam::Textures;
using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Volumes
	{

		ConstantMedium::ConstantMedium(
			IHittableCPtr boundary,
			double density,
			ITextureCPtr texture
		)
			: boundary{ std::move(boundary) }
			, neg_inv_density{ -1 / density }
			, phase_function{ std::make_shared<const Isotropic>(texture) }
		{ }

		bool ConstantMedium::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			HitRecord front, back;

			if (!boundary->hit(ray, -infinity, infinity, front))
				return false;

			if (!boundary->hit(ray, front.distance() + 1e-4, infinity, back))
				return false;

			if (front.distance() < min_distance)
				front = front.distance(min_distance);

			if (back.distance() > max_distance)
				back = back.distance(max_distance);

			if (front.distance() >= back.distance())
				return false;

			if (front.distance() < 0)
				front = front.distance(0);

			const auto ray_length = ray.direction().length();
			const auto distance_inside_boundary = (back.distance() - front.distance()) * ray_length;
			const auto hit_distance = neg_inv_density * std::log(random_double());

			if (hit_distance > distance_inside_boundary)
				return false;

			const auto distance = front.distance() + hit_distance / ray_length;

			record = HitRecord(
				distance,
				ray.at(distance),
				Vec3::unit_x,		// arbitrary
				Vec2::unit_x,		// arbitrary
				true,				// arbitrary
				phase_function);

			return true;
		}

		bool ConstantMedium::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			return boundary->bounding_box(begin_time, end_time, bounding_box);
		}

	}
}