#pragma once
#include "../MasterEngineLibAggregator/GameObject.h"
#include <mutex>

namespace CaptainEverythingAggregator {
	using namespace MasterEngine::LibAggregator;
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