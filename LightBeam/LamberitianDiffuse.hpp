#pragma once


#include "IMaterial.hpp"
#include "ITexture.hpp"
#include "ConstantTexture.hpp"


namespace LightBeam
{
	namespace Materials
	{
		class LambertianDiffuse : public IMaterial {
		private:
			Textures::ITextureCPtr _albedo;

		public:
			LambertianDiffuse(const Image::Color& albedo);

			LambertianDiffuse(Textures::ITextureCPtr albedo);

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& albedo,
				Rendering::Ray& scattered,
				double& pdf
			) const;

			double scattering_pdf(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				const Rendering::Ray& scattered) const;
		};
	}
}