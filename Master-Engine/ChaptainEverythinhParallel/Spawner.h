#pragma once
#include "../MasterEngineLibParallel/GameObject.h"
#include <mutex>

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;

	class Spawner :
		public GameObject
	{
	public:
		Spawner();
		~Spawner();

		void start_up() override;
		void update() override;

		void add_player_hit();
		void add_enemy_hit();

		static Spawner* get_single_ton();
	private:
		static Spawner* single_ton_;

		int spawn_count_;
		int player_hits_;
		int enemy_kills_;

		float internal_timer;
		float spawn_time;
		float spawn_position_;

		std::mutex player_hit_mutex_;
		std::mutex enemy_hit_mutex_;
	};
}
