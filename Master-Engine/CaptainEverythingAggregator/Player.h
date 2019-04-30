#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
	class Player :
		public GameObject
	{
	public:
		Player(sf::Vector2f);
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
