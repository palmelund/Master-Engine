#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;
	class Boss :
		public GameObject
	{
	public:
		Boss();
		~Boss();

		void start_up() override;
		void update() override;
		void OnCollision(GameObject* collider) override;

		void loss_shield();

	private:
		int size_;
		int shield_amount_;
	};

}