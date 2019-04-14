#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"
#include <mutex>

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;

	class BackgroundElement :
		public GameObject
	{
	public:
		BackgroundElement(sf::Vector2f);
		~BackgroundElement();

		void update() override;
		void OnCollision(GameObject* collider) override;

	private:
		int size_;
	};

}