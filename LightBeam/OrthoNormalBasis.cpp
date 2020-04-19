#include "OrthoNormalBasis.hpp"


namespace LightBeam
{
	namespace Math
	{

		OrthoNormalBasis::OrthoNormalBasis(
			const Vec3& u,
			const Vec3& v,
			const Vec3& w)
		{
			axes[0] = u;
			axes[1] = v;
			axes[2] = w;
		}

		const Vec3& OrthoNormalBasis::operator[] (int i) const
		{
			return axes[i];
		}

		const Vec3& OrthoNormalBasis::u() const noexcept
		{
			return axes[0];
		}

		const Vec3& OrthoNormalBasis::v() const noexcept
		{
			return axes[1];
		}

		const Vec3& OrthoNormalBasis::w() const noexcept
		{
			return axes[2];
		}

		Vec3 OrthoNormalBasis::local(double a, double b, double c) const
		{
			return a * u() + b * v() + c * w();
		}

		Vec3 OrthoNormalBasis::local(const Vec3& a) const
		{
			return a.x() * u() + a.y() * v() + a.z() * w();
		}

		OrthoNormalBasis OrthoNormalBasis::from(const Vec3& n)
		{
			auto w = n.norm();
			auto a = (std::abs(w.x()) > 0.9) ? Vec3::unit_y : Vec3::unit_x;
			auto v = Vec3::cross(w, a).norm();
			auto u = Vec3::cross(w, v);
			return OrthoNormalBasis(u, v, w);
		}
	}
}