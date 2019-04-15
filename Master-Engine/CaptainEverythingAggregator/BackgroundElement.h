#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;

	class BackgroundElement :
		public GameObject
	{
	public:
		BackgroundElement(sf::Vector2f);
		~BackgroundElement();

		void update() override;
		void on_collision(GameObject* collider) override;

	private:
		int size_;
	};

}