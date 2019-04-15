#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;
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