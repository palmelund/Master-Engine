#pragma once
#include<vector>
#include<queue>
#include <mutex>
#include <map>
#include <atomic>
#include <thread>
#include "BaseDelta.h"

namespace MasterEngine {
	namespace LibAggregator {

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

			std::atomic_int working_threads;

			static std::map<std::thread::id, std::map<void*, BaseDelta*>> deltas;
			static std::vector<std::thread::id> threads_ids;
			const unsigned thread_count = std::thread::hardware_concurrency();
		private:
			void worker_thread_loop();
			std::condition_variable condition_;
			std::vector<std::thread> pool_;

			bool terminate_;
		};

	}
}
