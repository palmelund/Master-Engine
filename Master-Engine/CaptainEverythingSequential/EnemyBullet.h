#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;

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