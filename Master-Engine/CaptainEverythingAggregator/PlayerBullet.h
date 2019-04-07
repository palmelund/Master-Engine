#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"
#include <mutex>

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
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
