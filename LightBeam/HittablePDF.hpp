#pragma once


#include "ProbabilityDensityFunction.hpp"
#include "IHittable.hpp"


namespace LightBeam
{
	namespace Rendering
	{

		class HittablePDF : public ProbabilityDensityFunction
		{
		private:
			Math::Vec3 _origin;
			IHittableCPtr _hittable;

		public:
			HittablePDF(
				IHittableCPtr hittable,
				const Math::Vec3& origin);

			double value(const Math::Vec3& direction) const;

			Math::Vec3 generate() const;
		};

	}
}


