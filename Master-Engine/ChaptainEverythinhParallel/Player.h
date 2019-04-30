#pragma once
#include "../MasterEngineLibParallel/GameObject.h"

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;
	class Player :
		public GameObject
	{
	public:
		Player();
		~Player();

		void start_up() override;
		void update() override;
		void on_collision(GameObject* collider) override;

	private:
		int size_;
		float fire_rate_;
		float fire_rate_cooldown_;
		float speed;
	};
}
