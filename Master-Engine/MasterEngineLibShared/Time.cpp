#include "stdafx.h"
#include "Time.h"
#include <chrono>

namespace MasterEngine {
	namespace LibShared {

		float Time::delta_time_{};
		long long Time::start_time_{};
		long long Time::frame_time_{ };

		static long long current_time_stamp() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}

		float Time::delta_time()
		{
			return delta_time_;
		}

		long long Time::startup_time()
		{
			return start_time_;
		}

		long long Time::system_time()
		{
			return current_time_stamp();
		}

		long long Time::frame_time()
		{
			return frame_time_;
		}

		void Time::tick()
		{
			const auto now = current_time_stamp();

			delta_time_ = static_cast<float>(now - frame_time_) / 1000;
			frame_time_ = now;
		}

		void Time::start_up()
		{
			start_time_ = current_time_stamp();
			frame_time_ = start_time_;
		}

	}
}