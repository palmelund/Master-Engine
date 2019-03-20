#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <queue>
#include <unordered_set>
#include <set>

namespace MasterEngine
{
	namespace LibParallel {

#define LOG_DELTA_TIMES

		class GameEngine
		{
		public:
			GameEngine() = delete;
			~GameEngine() = delete;
			static void init();
			static void run();

			static unsigned long long get_new_id();

			static  void Instantiate(GameObject*, sf::Vector2f);

			static void add_game_object(GameObject* game_object);
			static void add_collider(GameObject* game_object);
			static void remove_collider(GameObject* game_object);

			static void remove_game_object(GameObject* game_object);

			static std::vector<GameObject*>& get_gamestate();
			static std::unordered_set<GameObject*>& get_destroyid_game_object();

		private:
			static unsigned long long incremental_id_;
			static std::vector<GameObject*> game_objects_;
			static std::unordered_set<GameObject*> destroyed_game_objects_;
			static std::unordered_set<GameObject*> collision_game_objects_;
#ifdef LOG_DELTA_TIMES
			static std::vector<float> delta_list_;
#endif

			static std::mutex add_game_object_mutex_;
			static std::mutex remove_game_object_mutex_;
			static std::mutex modify_collision_mutex_;
		};
	}
}
