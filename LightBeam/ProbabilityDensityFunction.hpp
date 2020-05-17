#pragma once


#include "Vec3.hpp"


namespace LightBeam
{
	namespace Rendering
	{

		class ProbabilityDensityFunction
		{
		public:
			virtual double value(const Math::Vec3& direction) const = 0;

			virtual Math::Vec3 generate() const = 0;
		};

	}
}