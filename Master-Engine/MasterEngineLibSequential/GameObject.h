#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"

namespace MasterEngine {
	namespace LibShared {
		enum class Tags;
	}
}

namespace MasterEngine {
	namespace LibSequential {
		using namespace LibShared;

		class Collider;

		class GameObject
		{
		public:
			explicit GameObject(bool enable_collisions = false);
			virtual ~GameObject();

			GameObject(const GameObject&) = delete;
			GameObject& operator=(const GameObject&) = delete;

			GameObject(GameObject&&) = default;
			GameObject& operator=(GameObject&&) = default;

			unsigned long long get_id() const noexcept;

			virtual void start_up();
			virtual void update();
			virtual void on_collision(GameObject* collider);
			void collision_check();

			void set_sprite(int sprite_position);
			void unset_sprite();

			void add_collider(Collider* collider);

			template<typename CONTAINER>
			void add_colliders(const CONTAINER& collider);

			std::vector<Collider*>& get_colliders();


			void set_position(sf::Vector2f);
			sf::Vector2f get_position() const;

			void set_tag(Tags);
			Tags get_tag() const;

			float get_width_size() const;
			float get_height_size() const;
			void set_scale(float, float);
			void set_size(float, float);
			void add_velocity(sf::Vector2f);
			void set_velocity(sf::Vector2f);

			sf::Vector2f get_scaled_size() const;

			sf::Vector2f get_velocity() const;

			int sprite_pos() const noexcept;

		protected:
			int sprite_pos_{};

		private:
			sf::Vector2f velocity_;
			bool enable_collisions_;
			unsigned long long id_;


			std::vector<Collider*> colliders_ = std::vector<Collider*>{};
			Tags tag_;
			sf::Vector2f position_ = sf::Vector2f{ 0, 0 };

			bool draw_ = false;

			float height_scale_{};
			float width_scale_{};

			sf::Vector2f size_;
		};
	}
}
