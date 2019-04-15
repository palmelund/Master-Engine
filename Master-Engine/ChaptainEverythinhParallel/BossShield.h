#pragma once
#include "../MasterEngineLibParallel/GameObject.h"

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;
	class Boss;

	class BossShield :
		public GameObject
	{
	public:
		BossShield(Boss*, int);
		~BossShield();

		void update() override;
		void on_collision(GameObject* collider) override;
	private:
		Boss* boss_;
		float position_;
		float circumference_;

	};

}