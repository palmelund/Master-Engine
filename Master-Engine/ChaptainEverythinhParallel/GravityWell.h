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

		void OnCollision(GameObject* collider) override;
	};
}
