#pragma once
#include "../MasterEngineLibParallel/GameObject.h"

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;
	class PlayerBullet :
		public GameObject
	{
	public:
		PlayerBullet();
		~PlayerBullet();

		void update() override;
		void on_collision(GameObject* collider) override;

	private:
		int size_;
	};
}
