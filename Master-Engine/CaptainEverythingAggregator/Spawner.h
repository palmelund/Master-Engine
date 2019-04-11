#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"
#include "../MasterEngineLibAggregator/IntWrapper.h"
#include <mutex>

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;

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
		IntWrapper player_hits_;
		IntWrapper enemy_kills_;

		float internal_timer;
		float spawn_time;
		float spawn_position_;
	};
}
