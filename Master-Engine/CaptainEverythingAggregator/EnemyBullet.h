#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
	class EnemyBullet :
		public GameObject
	{
	public:
		EnemyBullet(sf::Vector2f);
		~EnemyBullet();

		void start_up() override;
		void update() override;

	private:
		int size_;
	};

}