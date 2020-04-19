#pragma once


#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Materials
	{
		class Metal : public IMaterial {
		private:
			Image::Color _albedo;
			double _fuzz;

		public:
			Metal(const Image::Color& albedo, double fuzz);

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered,
				double& pdf) const;
		};
	}
}