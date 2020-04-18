#include "BoundingVolumeNode.hpp"
#include "Random.hpp"


using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Rendering
	{
		BoundingVolumeNode::BoundingVolumeNode(
			std::shared_ptr<const BoundingVolumeNode> left,
			std::shared_ptr<const BoundingVolumeNode> right
		)
			: _left{ std::move(left) }
			, _right{ std::move(right) }
		{
			AxisAlignedBoundingBox left_box, right_box;
			_left->bounding_box(0.0, 1.0, left_box);
			_right->bounding_box(0.0, 1.0, right_box);

			_box = AxisAlignedBoundingBox::surrounding_box(left_box, right_box);
		}

		BoundingVolumeNode::BoundingVolumeNode(
			std::vector<std::shared_ptr<const IHittable>>& hittables,
			double begin_time,
			double end_time )
			: BoundingVolumeNode(hittables, 0, hittables.size(), begin_time, end_time)
		{}

		BoundingVolumeNode::BoundingVolumeNode(
			std::vector<std::shared_ptr<const IHittable>>& hittables,
			size_t start,
			size_t end,
			double begin_time,
			double end_time)
		{
			int axis = random_int(0, 2);
			auto comparator = (axis == 0) ? box_x_compare
						    : (axis == 1) ? box_y_compare
									      : box_z_compare;

			size_t span = end - start;

			if (span == 1) {
				_left = _right = hittables[start];
			}
			else if (span == 2) {
				if (comparator(hittables[start], hittables[start + 1])) {
					_left = hittables[start];
					_right = hittables[start + 1];
				}
				else {
					_left = hittables[start];
					_right = hittables[start + 1];
				}
			}
			else {
				std::sort(
					hittables.begin() + start,
					hittables.begin() + end,
					comparator);

				auto mid = start + span / 2;
				_left = std::make_shared<BoundingVolumeNode>(hittables, start, mid, begin_time, end_time);
				_right = std::make_shared<BoundingVolumeNode>(hittables, mid, end, begin_time, end_time);
			}

			AxisAlignedBoundingBox left_box, right_box;

			if (!_left->bounding_box(begin_time, end_time, left_box)
				|| !_right->bounding_box(begin_time, end_time, right_box))
				std::cerr << "No bounding box in BoundingVolumeNode constructor" << std::endl;

			_box = AxisAlignedBoundingBox::surrounding_box(left_box, right_box);
		}

		bool BoundingVolumeNode::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			if (!_box.hit(ray, min_distance, max_distance))
				return false;

			bool hit_left = _left->hit(ray, min_distance, max_distance, record);
			bool hit_right = _right->hit(ray, min_distance, hit_left ? record.distance() : max_distance, record);

			return hit_left || hit_right;
		}

		bool BoundingVolumeNode::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = _box;
			return true;
		}

		bool BoundingVolumeNode::box_compare(
			std::shared_ptr<const IHittable> a,
			std::shared_ptr<const IHittable> b,
			int axis)
		{
			AxisAlignedBoundingBox box_a;
			AxisAlignedBoundingBox box_b;

			if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
				std::cerr << "No bounding box in BoundingVolumeNode constructor" << std::endl;

			return box_a.min()[axis] < box_b.min()[axis];
		}

		bool BoundingVolumeNode::box_x_compare(
			std::shared_ptr<const IHittable> a,
			std::shared_ptr<const IHittable> b) {
			return box_compare(a, b, 0);
		}

		bool BoundingVolumeNode::box_y_compare(
			std::shared_ptr<const IHittable> a,
			std::shared_ptr<const IHittable> b) {
			return box_compare(a, b, 1);
		}

		bool BoundingVolumeNode::box_z_compare(
			std::shared_ptr<const IHittable> a,
			std::shared_ptr<const IHittable> b) {
			return box_compare(a, b, 2);
		}

	}
}