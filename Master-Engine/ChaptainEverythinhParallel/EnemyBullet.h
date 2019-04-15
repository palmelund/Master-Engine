#pragma once
#include "../MasterEngineLibParallel/GameObject.h"

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;
	class EnemyBullet :
		public GameObject
	{
	public:
		EnemyBullet();
		~EnemyBullet();

		void start_up() override;
		void update() override;

	private:
		int size_;
	};

}