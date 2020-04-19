#include "LamberitianDiffuse.hpp"
#include "OrthoNormalBasis.hpp"


using namespace LightBeam::Image;
using namespace LightBeam::Math;
using namespace LightBeam::Rendering;
using namespace LightBeam::Textures;


namespace LightBeam
{
	namespace Materials
	{

		LambertianDiffuse::LambertianDiffuse(const Color& albedo)
			: _albedo{ std::make_shared<const ConstantTexture>(albedo) }
		{}

		LambertianDiffuse::LambertianDiffuse(ITextureCPtr albedo)
			: _albedo{ std::move(albedo) }
		{}

		bool LambertianDiffuse::scatter(
			const Ray& ray,
			const HitRecord& hit_record,
			Image::Color& albedo,
			Ray& scattered,
			double& pdf
		) const {
			auto uvw = OrthoNormalBasis::from(hit_record.normal());
			auto scatter_direction = uvw.local(Vec3::random_cosine_direction());

			scattered = Ray(
				hit_record.point(),
				scatter_direction,
				ray.time());

			albedo = _albedo->value(hit_record.uv(), hit_record.point());

			pdf = Vec3::dot(uvw.w(), scattered.direction()) / M_PI;

			return true;
		}

		double LambertianDiffuse::scattering_pdf(
			const Ray& ray,
			const HitRecord& hit_record,
			const Ray& scattered
		) const {
			auto cosine = Vec3::dot(hit_record.normal(), scattered.direction().norm());
			return cosine < 0 ? 0 : cosine / M_PI;
		}

	}
}