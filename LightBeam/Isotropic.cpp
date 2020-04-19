#include "Isotropic.hpp"
#include "Random.hpp"


using namespace LightBeam::Image;
using namespace LightBeam::Math;
using namespace LightBeam::Rendering;


namespace LightBeam
{
	namespace Materials
	{

		Isotropic::Isotropic(Textures::ITextureCPtr albedo)
			: albedo{ std::move(albedo) }
		{}

		bool Isotropic::scatter(
			const Ray& ray,
			const HitRecord& hit_record,
			Color& attenuation,
			Ray& scattered,
			double& pdf) const
		{
			scattered = Ray(
				ray.origin(),
				Vec3::random_in_unit_sphere(),
				ray.time());

			attenuation = albedo->value(
				hit_record.uv(),
				hit_record.point());

			return true;
		}

	}
}