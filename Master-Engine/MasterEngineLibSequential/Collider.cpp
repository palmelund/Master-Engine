#include "stdafx.h"
#include "Collider.h"
#include "SFML/Graphics.hpp"

namespace MasterEngine {
	namespace LibSequential {

		Collider::Collider(const sf::Vector2f local_position, const sf::Vector2f size) : local_position(local_position), size(size)
		{

		}

		Collider::Collider(Collider&& collider) noexcept = default;

		Collider& Collider::operator=(Collider&& collider) noexcept = default;

		Collider::~Collider() = default;

		Transform Collider::get_collider() const
		{
			Transform transform{};
			const auto owner_pos = owner_->get_position();
			transform.pos_x = local_position.x + owner_pos.x;
			transform.pos_y = local_position.y + owner_pos.y;
			transform.size_x = size.x;
			transform.size_y = size.y;
			return transform;
		}

		void Collider::set_owner(GameObject* owner)
		{
			owner_ = owner;
		}

		GameObject* Collider::get_owner() const
		{
			return owner_;
		}

		bool Collider::collider_overlap(const Transform transform1, const Transform transform2)
		{
			const auto l1_x = transform1.pos_x;
			const auto l1_y = transform1.pos_y;
			const auto r1_x = transform1.pos_x + transform1.size_x;
			const auto r1_y = transform1.pos_y + transform1.size_y;
			const auto l2_x = transform2.pos_x;
			const auto l2_y = transform2.pos_y;
			const auto r2_x = transform2.pos_x + transform2.size_x;
			const auto r2_y = transform2.pos_y + transform2.size_y;

			// If one rectangle is on left side of other
			if (l1_x > r2_x || l2_x > r1_x) {
				return false;
			}

			// If one rectangle is above other
			if (l1_y > r2_y || l2_y > r1_y) {

				return false;
			}

			return true;
		}

	}
}