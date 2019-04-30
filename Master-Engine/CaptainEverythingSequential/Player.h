#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;

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