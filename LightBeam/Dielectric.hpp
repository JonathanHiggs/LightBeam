#pragma once


#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Materials
	{
		class Dielectric : public IMaterial {
		private:
			double _refractive_index;

		public:
			Dielectric(double refractive_index)
				: _refractive_index{ refractive_index }
			{}

			static std::shared_ptr<const Dielectric> glass() {
				return std::make_shared<const Dielectric>(1.45);
			}

			static std::shared_ptr<const Dielectric> diamond() {
				return std::make_shared<const Dielectric>(2.4);
			}

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered
			) const
			{
				attenuation = Image::Color::WHITE;

				auto etai_over_etat = hit_record.front_face()
					? 1.0 / _refractive_index
					: _refractive_index;

				const auto unit_direction = ray.direction().norm();
				auto cos_theta = std::min(Math::Vec3::dot(-unit_direction, hit_record.normal()), 1.0);
				auto sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
				auto reflect_prod = schlick(cos_theta, etai_over_etat);

				if (etai_over_etat * sin_theta > 1.0 || Util::random_double() < reflect_prod) {
					// reflect
					const auto reflected = Math::Vec3::reflect(unit_direction, hit_record.normal());
					scattered = Rendering::Ray(hit_record.point(), reflected, ray.time());
					return true;
				}
				else {
					// refract
					const auto refracted = Math::Vec3::refract(
						unit_direction, hit_record.normal(), etai_over_etat);
					scattered = Rendering::Ray(hit_record.point(), refracted, ray.time());
				}

				return true;
			}

		private:
			double schlick(double cosine, double refractive_index) const {
				// approximate probability of reflecting rather than refracting
				auto r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
				r0 = r0 * r0;
				return r0 + (1.0 - r0) * std::pow((1.0 - cosine), 5.0);
			}
		};
	}
}