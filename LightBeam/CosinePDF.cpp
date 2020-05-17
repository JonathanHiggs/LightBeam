#include "CosinePDF.hpp"


using namespace LightBeam::Math;


namespace LightBeam
{
	namespace Rendering
	{

		CosinePDF::CosinePDF(const Vec3& v)
			: _basis{ OrthoNormalBasis::from(v) }
		{}

		double CosinePDF::value(const Vec3& direction) const
		{
			auto cosine = Vec3::dot(direction.norm(), _basis.w());
			return (cosine <= 0) ? 0 : cosine / M_PI;
		}

		Vec3 CosinePDF::generate() const
		{
			return _basis.local(Vec3::random_cosine_direction());
		}

	}
}

