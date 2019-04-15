#pragma once
namespace MasterEngine
{
	namespace LibShared {

		class Time
		{
		public:
			Time() = delete;
			~Time() = delete;

			static float delta_time();
			static long long startup_time();
			static long long system_time();
			static long long frame_time();
			static void tick();
			static void start_up();
		private:
			static float delta_time_;
			static long long start_time_;
			static long long frame_time_;
		};

	}
}