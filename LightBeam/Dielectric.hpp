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
			Dielectric(double refractive_index);

			static std::shared_ptr<const Dielectric> glass();
			static std::shared_ptr<const Dielectric> diamond();

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& albedo,
				Rendering::Ray& scattered,
				double& pdf
			) const;

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