#pragma once


#include "Color.hpp"
#include "IHittable.hpp"
#include "Ray.hpp"

#include "memory.hpp"


namespace LightBeam
{
	namespace Materials
	{

		class IMaterial {
		public:
			virtual bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& albedo,
				Rendering::Ray& scattered,
				double& pdf) const = 0;

			virtual double scattering_pdf(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				const Rendering::Ray& scattered) const
			{
				return 0;
			}

			virtual Image::Color emitted(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				const Math::Vec2& uv,
				const Math::Vec3& point) const
			{
				return Math::Vec3::zero;
			}
		};

		DECLARE_STD_PTR(IMaterial)

	}
}