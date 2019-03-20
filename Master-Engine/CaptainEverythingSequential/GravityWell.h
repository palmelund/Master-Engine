#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;

	class GravityWell :
		public GameObject
	{
	public:
		GravityWell();
		~GravityWell();

		void OnCollision(GameObject* collider) override;
	};

}