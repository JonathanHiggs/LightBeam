#include "Dielectric.hpp"


using namespace LightBeam::Image;
using namespace LightBeam::Math;
using namespace LightBeam::Rendering;
using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Materials
	{

		Dielectric::Dielectric(double refractive_index)
			: _refractive_index{ refractive_index }
		{}

		std::shared_ptr<const Dielectric> Dielectric::glass() {
			return std::make_shared<const Dielectric>(1.45);
		}

		std::shared_ptr<const Dielectric> Dielectric::diamond() {
			return std::make_shared<const Dielectric>(2.4);
		}

		bool Dielectric::scatter(
			const Ray& ray,
			const HitRecord& hit_record,
			Color& albedo,
			Ray& scattered,
			double& pdf
		) const
		{
			albedo = Color::WHITE;

			auto etai_over_etat = hit_record.front_face()
				? 1.0 / _refractive_index
				: _refractive_index;

			const auto unit_direction = ray.direction().norm();
			auto cos_theta = ffmin(Vec3::dot(-unit_direction, hit_record.normal()), 1.0);
			auto sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
			auto reflect_prod = schlick(cos_theta, etai_over_etat);

			if (etai_over_etat * sin_theta > 1.0 || random_double() < reflect_prod) {
				// reflect
				const auto reflected = Vec3::reflect(unit_direction, hit_record.normal());
				scattered = Ray(hit_record.point(), reflected, ray.time());
				return true;
			}
			else {
				// refract
				const auto refracted = Vec3::refract(
					unit_direction, hit_record.normal(), etai_over_etat);
				scattered = Ray(hit_record.point(), refracted, ray.time());
			}

			return true;
		}

	}
}