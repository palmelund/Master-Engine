#pragma once
#include "SFML/Graphics.hpp"
#include "Collider.h"
#include <mutex>
#include "Vector2Wrapper.h"

namespace MasterEngine {
	namespace LibShared {
		enum class Tags;
	}
}

namespace MasterEngine
{
	namespace LibAggregator {
		using namespace MasterEngine::LibShared;
		class Collider;//Needed to break cirkuler pointer.

		class GameObject
		{
		public:
			explicit GameObject(bool collision_code = false, bool takes_input=false);
			virtual ~GameObject();

			GameObject(const GameObject&) = delete;
			GameObject& operator=(const GameObject&) = delete;

			GameObject(GameObject&&) = delete;
			GameObject& operator=(GameObject&&) = delete;

			unsigned long long get_id() const noexcept;

			void remove_game_object();

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
			void set_position(sf::Vector2f position, int priority);
			sf::Vector2f get_position();

			void set_tag(LibShared::Tags);
			Tags get_tag() const;

			float get_width_size() const;
			float get_height_size() const;
			void set_scale(float, float);
			void set_size(float, float);
			void add_velocity(sf::Vector2f);
			void set_velocity(sf::Vector2f);

			sf::Vector2f get_scaled_size() const;

			sf::Vector2f get_velocity();

			int sprite_pos() const noexcept;

			bool need_input();

		protected:
			int sprite_pos_{};
			Vector2Wrapper velocity_;
			Vector2Wrapper position_ = Vector2Wrapper{};

		private:
			bool collision_code_;
			bool takes_input_;
			unsigned long long id_;


			std::vector<Collider*> colliders_ = std::vector<Collider*>{};
			Tags tag_;


			bool draw_ = false;

			float height_scale_{};
			float width_scale_{};

			sf::Vector2f size_;

			std::mutex collider_modify_mutex_;
		};
	}
}
