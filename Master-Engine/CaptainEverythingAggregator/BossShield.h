#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
	class Boss;

	class BossShield :
		public GameObject
	{
	public:
		BossShield(Boss*, int);
		~BossShield();

		void update() override;
		void OnCollision(GameObject* collider) override;
	private:
		Boss* boss_;
		float position_;
		float circumference_;

	};

}