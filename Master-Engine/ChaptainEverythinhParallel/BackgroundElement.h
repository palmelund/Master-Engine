#pragma once
#include "../MasterEngineLibParallel/GameObject.h"

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;

	class BackgroundElement :
		public GameObject
	{
	public:
		BackgroundElement();
		~BackgroundElement();

		void update() override;
		void on_collision(GameObject* collider) override;

	private:
		int size_;
	};

}