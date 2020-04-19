#pragma once


#include "Vec3.hpp"


namespace LightBeam
{
	namespace Math
	{

		class OrthoNormalBasis
		{
		private:
			Vec3 axes[3];

		public:
			OrthoNormalBasis(
				const Vec3& u,
				const Vec3& v,
				const Vec3& w);

			const Vec3& operator[] (int i) const;

			const Vec3& u() const noexcept;
			const Vec3& v() const noexcept;
			const Vec3& w() const noexcept;

			Vec3 local(double a, double b, double c) const;
			Vec3 local(const Vec3& a) const;

			static OrthoNormalBasis from(const Vec3&);
		}

	}
}