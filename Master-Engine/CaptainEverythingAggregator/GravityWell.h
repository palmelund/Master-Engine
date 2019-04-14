#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
	class GravityWell :
		public GameObject
	{
	public:
		GravityWell(sf::Vector2f);
		~GravityWell();

		void OnCollision(GameObject* collider) override;
	};
}
