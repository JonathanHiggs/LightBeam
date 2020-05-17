#pragma once


#include "ProbabilityDensityFunction.hpp"
#include "OrthoNormalBasis.hpp"


namespace LightBeam
{
	namespace Rendering
	{

		class CosinePDF : public ProbabilityDensityFunction
		{
		private:
			Math::OrthoNormalBasis _basis;

		public:
			CosinePDF(const Math::Vec3& v);

			double value(const Math::Vec3& direction) const;

			Math::Vec3 generate() const;
		};

	}
}

