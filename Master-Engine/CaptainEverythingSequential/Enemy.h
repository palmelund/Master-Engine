#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

namespace CaptainEverythingSequential {
	using namespace MasterEngine::LibSequential;
	class Enemy :
		public GameObject
	{
	public:
		Enemy();
		~Enemy();

		void start_up() override;
		void update() override;

	private:
		int size_;
		float fire_rate_;
		float internal_timer;

	};

}