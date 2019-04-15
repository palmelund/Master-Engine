#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <queue>
#include <unordered_set>
#include "ThreadPool.h"
#include "VectorWrapper.h"

namespace MasterEngine
{
	namespace LibAggregator {

//#define LOG_DELTA_TIMES
#define LOG_CUMULATIVE_TIME

		class GameEngine
		{
		public:
			GameEngine() = delete;
			static void init();
			static void run();

			static unsigned long long get_new_id();

			static  void instantiate(GameObject*);

			static void add_game_object(GameObject* game_object);
			static void add_collider(GameObject* game_object);
			static void remove_collider(GameObject* game_object);

			static void remove_game_object(GameObject* game_object);

			static std::vector<GameObject*>& get_game_state();
			static std::unordered_set<GameObject*>& get_destroyed_game_object();
			static void merge_list(std::thread::id, std::thread::id);
			static std::unordered_set<GameObject*> destroyed_game_objects;
		private:
			static unsigned long long incremental_id_;
			static VectorWrapper<GameObject*> game_objects_;
			static VectorWrapper<GameObject*> collision_game_objects_;
#ifdef LOG_DELTA_TIMES
			static std::vector<float> delta_list_;
#endif

#ifdef LOG_CUMULATIVE_TIME
			static long long frame_count_;
			static float cumulative_time_;
#endif

			static ThreadPool thread_pool_;
		};
	}
}
