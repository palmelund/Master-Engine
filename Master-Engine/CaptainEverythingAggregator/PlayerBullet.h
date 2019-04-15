#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
	class PlayerBullet :
		public GameObject
	{
	public:
		PlayerBullet(sf::Vector2f);
		~PlayerBullet();

		void update() override;
		void on_collision(GameObject* collider) override;

	private:
		int size_;
	};
}
