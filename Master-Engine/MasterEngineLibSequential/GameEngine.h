#pragma once

#include "SFML/Graphics.hpp"

#include "GameObject.h"
#include <unordered_set>

//#define LOG_DELTA_TIMES
#define LOG_CUMULATIVE_TIME

namespace MasterEngine {
	namespace LibSequential {

		class GameEngine
		{
		public:
			GameEngine() = delete;
			static void init();
			static void run();

			static unsigned long long get_new_id();

			static  void instantiate(GameObject*, sf::Vector2f);

			static void add_game_object(GameObject* game_object);
			static void add_collider(GameObject* game_object);
			static void remove_collider(GameObject* game_object);

			static void remove_game_object(GameObject* game_object);

			static std::unordered_set<GameObject*>& get_game_state();
			static std::unordered_set<GameObject*>& get_destroyed_game_objects();

		private:
			static unsigned long long incremental_id_;
			static std::unordered_set<GameObject*> game_objects_;
			static std::unordered_set<GameObject*> destroyed_game_object_;
			static std::unordered_set<GameObject*> collision_game_object_;
#ifdef LOG_DELTA_TIMES
			static std::vector<float> delta_list_;
#endif

#ifdef LOG_CUMULATIVE_TIME
			static long long frame_count_;
			static float cumulative_time_;
#endif
		};
	}
}