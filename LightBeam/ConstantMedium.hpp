#pragma once


#include "IHittable.hpp"
#include "IMaterial.hpp"
#include "ITexture.hpp"


namespace LightBeam
{
	namespace Volumes
	{

		class ConstantMedium : public Rendering::IHittable
		{
		public:
			Rendering::IHittableCPtr boundary;
			Materials::IMaterialCPtr phase_function;
			double neg_inv_density;

			ConstantMedium(
				Rendering::IHittableCPtr boundary,
				double density,
				Textures::ITextureCPtr texture);

			bool hit(
				const Rendering::Ray& ray,
				double min_distance,
				double max_distance,
				Rendering::HitRecord& record) const;

			bool bounding_box(
				double begin_time,
				double end_time,
				Rendering::AxisAlignedBoundingBox& bounding_box) const;
		};

	}
}


