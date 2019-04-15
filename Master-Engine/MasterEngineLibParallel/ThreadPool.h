#pragma once
#include<vector>
#include<queue>
#include <mutex>
#include <atomic>

namespace MasterEngine {
	namespace LibParallel {

		class ThreadPool
		{
		public:
			ThreadPool();

			void create_thread_pool();
			void add_job(const std::function<void()>&);
			std::condition_variable condition_done;
			std::mutex queue_mutex;
			std::queue<std::function<void()>> job_queue;

			void terminate();

			std::atomic_int working_threads_{};
		private:
			void worker_thread_loop();
			std::condition_variable condition;
			std::vector<std::thread> Pool;
			bool terminate_;
		};

	}
}
