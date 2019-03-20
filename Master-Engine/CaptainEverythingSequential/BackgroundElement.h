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
		void OnCollision(GameObject* collider) override;

	private:
		int size_;
	};
}