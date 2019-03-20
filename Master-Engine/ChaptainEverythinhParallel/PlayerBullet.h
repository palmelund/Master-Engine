#pragma once
#include "../MasterEngineLibParallel/GameObject.h"
#include <mutex>

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;
	class PlayerBullet :
		public GameObject
	{
	public:
		PlayerBullet();
		~PlayerBullet();

		void update() override;
		void OnCollision(GameObject* collider) override;

	private:
		int size_;
	};
}
