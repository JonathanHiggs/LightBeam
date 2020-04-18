#pragma once

#include <iostream>

#include "IHittable.hpp"
#include "HittableList.hpp"


namespace LightBeam
{
	namespace Rendering
	{

		class BoundingVolumeNode : public IHittable {
		private:
			std::shared_ptr<const IHittable> _left;
			std::shared_ptr<const IHittable> _right;
			AxisAlignedBoundingBox _box;

		public:
			BoundingVolumeNode(
				std::shared_ptr<const BoundingVolumeNode> left,
				std::shared_ptr<const BoundingVolumeNode> right);

			BoundingVolumeNode(
				std::vector<std::shared_ptr<const IHittable>>& hittables,
				double begin_time,
				double end_time);

			BoundingVolumeNode(
				std::vector<std::shared_ptr<const IHittable>>& hittables,
				size_t start,
				size_t end,
				double begin_time,
				double end_time);

			bool hit(
				const Ray& ray,
				double min_distance,
				double max_distance,
				HitRecord& record) const;

			bool bounding_box(
				double begin_time,
				double end_time,
				AxisAlignedBoundingBox& bounding_box) const;

		private:
			static bool box_compare(
				std::shared_ptr<const IHittable> a,
				std::shared_ptr<const IHittable> b,
				int axis);

			bool static box_x_compare(
				std::shared_ptr<const IHittable> a,
				std::shared_ptr<const IHittable> b);

			bool static box_y_compare(
				std::shared_ptr<const IHittable> a,
				std::shared_ptr<const IHittable> b);

			bool static box_z_compare(
				std::shared_ptr<const IHittable> a,
				std::shared_ptr<const IHittable> b);
		};

	}
}