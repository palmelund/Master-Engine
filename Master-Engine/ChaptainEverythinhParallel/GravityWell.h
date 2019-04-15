#pragma once
#include "../MasterEngineLibParallel/GameObject.h"

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;
	class GravityWell :
		public GameObject
	{
	public:
		GravityWell();
		~GravityWell();

		void on_collision(GameObject* collider) override;
	};
}
