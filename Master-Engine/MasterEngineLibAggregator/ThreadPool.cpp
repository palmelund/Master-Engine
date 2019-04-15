#include "stdafx.h"

#include <thread>
#include <vector>
#include <mutex>
#include "ThreadPool.h"
#include <map>

namespace MasterEngine {
	namespace LibAggregator {

		std::vector<std::thread::id> ThreadPool::threads_ids{};
		std::map<std::thread::id, std::map<void*, BaseDelta*>> ThreadPool::deltas{};

		ThreadPool::ThreadPool() : working_threads(0), terminate_(false)
		{
		}

		void ThreadPool::create_thread_pool()
		{

			for (unsigned ii = 0; ii < thread_count; ii++)
			{
				pool_.emplace_back(std::bind(&ThreadPool::worker_thread_loop, this));
				deltas[pool_[ii].get_id()] = {};
				threads_ids.emplace_back(pool_[ii].get_id());
			}
		}

		void ThreadPool::add_job(const std::function<void()>& func)
		{
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				job_queue.push(func);
				++working_threads;
			}
			condition_.notify_one();
		}

		void ThreadPool::terminate()
		{
			terminate_ = true;
			condition_.notify_all();

			for (auto& t : pool_)
			{
				t.join();
			}
		}

		void ThreadPool::worker_thread_loop()
		{
			while (true)
			{
				std::function<void()> current_job;
				{
					std::unique_lock<std::mutex> lock(queue_mutex);
					if (working_threads == 0)
					{
						condition_done.notify_one();
					}
					condition_.wait(lock, [this] {return !job_queue.empty() || terminate_; });

					if (terminate_)
					{
						--working_threads;
						return;
					}

					current_job = job_queue.front();
					job_queue.pop();
				}

				current_job();

				--working_threads;
			}
		}

	}
}
