#include "HittablePDF.hpp"


using namespace LightBeam::Math;


namespace LightBeam
{
	namespace Rendering
	{

		HittablePDF::HittablePDF(
			IHittableCPtr hittable,
			const Vec3& origin
		)
			: _hittable{ std::move(hittable) }
			, _origin{ origin }
		{}

		double HittablePDF::value(const Vec3& direction) const
		{
			return _hittable->pdf_value(_origin, direction);
		}

		Vec3 HittablePDF::generate() const
		{
			return _hittable->random_from_source(_origin);
		}

	}
}