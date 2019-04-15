#pragma once
#include "../MasterEngineLibParallel/GameObject.h"
#include <mutex>

namespace CaptainEverythingParallel {
	using namespace MasterEngine::LibParallel;
	class Boss :
		public GameObject
	{
	public:
		Boss();
		~Boss();

		void start_up() override;
		void update() override;
		void on_collision(GameObject* collider) override;

		void loss_shield();

	private:
		int size_;
		int shield_amount_;

		std::mutex shield_amount_mutex_;
	};

}