#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"
#include <mutex>

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
	class Boss :
		public GameObject
	{
	public:
		Boss(sf::Vector2f);
		~Boss();

		void start_up() override;
		void update() override;
		void OnCollision(GameObject* collider) override;

		void loss_shield();

	private:
		int size_;
		int shield_amount_;

		std::mutex shield_amount_mutex_;
	};

}