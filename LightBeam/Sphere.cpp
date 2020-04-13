#include "Sphere.hpp"


bool Sphere::hit(
	const Ray& ray,
	double min_distance,
	double max_distance,
	HitRecord& record) const
{
	const auto oc = ray.origin() - _center;
	const auto a = Vec3::dot(ray.direction(), ray.direction());
	const auto half_b = Vec3::dot(oc, ray.direction());
	const auto c = Vec3::dot(oc, oc) - _radius * _radius;

	const auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0)
		return false;

	const auto distance = (-half_b - std::sqrt(discriminant)) / a;

	if (distance < min_distance || distance > max_distance)
		return false;

	const auto point = ray.at(distance);
	auto normal = outward_normal(point);
	const auto inside = Vec3::dot(ray.direction(), normal) > 0.0;

	if (inside)
		normal = -normal;

	record = HitRecord(distance, point, normal, !inside, _material);

	return true;
}