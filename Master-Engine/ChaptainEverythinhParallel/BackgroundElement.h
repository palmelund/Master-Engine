#pragma once
#include "../MasterEngineLibParallel/GameObject.h"
#include <mutex>

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;

	class BackgroundElement :
		public GameObject
	{
	public:
		BackgroundElement();
		~BackgroundElement();

		void update() override;
		void OnCollision(GameObject* collider) override;

	private:
		int size_;
	};

}