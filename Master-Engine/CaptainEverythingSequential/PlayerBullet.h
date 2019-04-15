#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;

	class PlayerBullet :
		public GameObject
	{
	public:
		PlayerBullet();
		~PlayerBullet();

		void update() override;
		void on_collision(GameObject* collider) override;

	private:
		int size_;
	};

}