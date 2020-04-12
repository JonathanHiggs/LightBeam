#include "sphere.hpp"


bool Sphere::hit(
	const Ray& ray,
	double min_distance,
	double max_distance,
	HitRecord& record) const
{
	const auto oc = ray.origin() - _center;
	const auto a = dot(ray.direction(), ray.direction());
	const auto half_b = dot(oc, ray.direction());
	const auto c = dot(oc, oc) - _radius * _radius;

	const auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return false;

	const auto distance = (-half_b - std::sqrt(discriminant)) / a;

	if (distance < min_distance || distance > max_distance)
		return false;

	const auto point = ray.at(distance);
	auto normal = outward_normal(point);
	const auto inside = dot(ray.direction(), normal) > 0.0;

	if (inside)
		normal = -normal;

	record = HitRecord(distance, point, normal, !inside);

	return true;
}