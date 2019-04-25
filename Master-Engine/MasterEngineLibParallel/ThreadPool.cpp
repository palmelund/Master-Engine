#include "stdafx.h"

#include <thread>
#include <vector>
#include <mutex>
#include "ThreadPool.h"
#include <map>

namespace MasterEngine {
	namespace LibParallel {
		ThreadPool::ThreadPool() : working_threads_(0), terminate_(false)
		{
		}

		void ThreadPool::create_thread_pool()
		{
#ifdef SINGLE_CORE_TEST
			const auto thread_count = 1;
#else
			const auto thread_count = std::thread::hardware_concurrency();
#endif


			for (unsigned t = 0; t < thread_count; t++)
			{
				Pool.emplace_back(std::bind(&ThreadPool::worker_thread_loop, this));
			}
		}

		void ThreadPool::add_job(const std::function<void()>& func)
		{
			{
				std::unique_lock<std::mutex> lock(queue_mutex);
				job_queue.push(func);
				++working_threads_;
			}
			condition.notify_one();
		}

		void ThreadPool::terminate()
		{
			terminate_ = true;
			condition.notify_all();

			for (auto& t : Pool)
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
					if (working_threads_ == 0)
					{
						condition_done.notify_one();
					}
					condition.wait(lock, [this] {return !job_queue.empty() || terminate_; });

					if (terminate_)
					{
						--working_threads_;
						return;
					}

					current_job = job_queue.front();
					job_queue.pop();
				}

				current_job(); // function<void()> type

				--working_threads_;
			}
		}

	}
}
