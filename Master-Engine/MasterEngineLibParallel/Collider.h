#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Transform.h"

namespace MasterEngine {
	namespace LibParallel {

		class  GameObject;

		class Collider
		{
		public:
			Collider(sf::Vector2f local_position, sf::Vector2f size);
			sf::Vector2f local_position;
			sf::Vector2f size;

			Transform get_collider() const;

			void set_owner(GameObject*);
			GameObject* get_owner() const;
			static bool collider_overlap(Transform transform1, Transform transform2);

		private:
			GameObject* owner_;

		};
	}
}