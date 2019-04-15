#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Transform.h"

namespace MasterEngine
{
	namespace LibSequential {

		class  GameObject;

		class Collider
		{
		public:
			Collider(sf::Vector2f local_position, sf::Vector2f size);
			Collider(const Collider& collider) = delete;
			Collider(Collider&& collider) noexcept;
			Collider& operator=(const Collider& collider) = delete;
			Collider& operator=(Collider&& collider) noexcept;
			~Collider();
			sf::Vector2f local_position;
			sf::Vector2f size;

			Transform get_collider() const;

			void set_owner(GameObject*);
			GameObject* get_owner() const;
			static bool collider_overlap(Transform transform1, Transform transform2);

		private:
			GameObject* owner_{};

		};
	}
}