#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;

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
	};
}
