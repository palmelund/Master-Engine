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

		ThreadPool::ThreadPool()
		{
			working_threads_ = 0;
			terminate_ = false;
		}

		ThreadPool::~ThreadPool()
		= default;

		void ThreadPool::CreateThreadPool()
		{

			for (int ii = 0; ii < thread_count; ii++)
			{
				Pool.emplace_back(std::bind(&ThreadPool::InfiniteLoop, this));
				deltas[Pool[ii].get_id()] = {};
				threads_ids.emplace_back(Pool[ii].get_id());
			}
		}

		void ThreadPool::ClearThreadPool()
		{
			std::queue<std::function<void()>> queue;
			std::swap(JobQueue, queue);

			for (auto i = 0; i < Pool.size(); i++)
			{
				JobQueue.push(nullptr);
			}

			condition.notify_all();

			for (auto& t : Pool)
			{
				t.join();
			}
		}

		void ThreadPool::AddJob(std::function<void()> func)
		{
			{
				std::unique_lock<std::mutex> lock(Queue_Mutex);
				JobQueue.push(func);
				++working_threads_;
			}
			condition.notify_one();
		}

		//void ThreadPool::AddJobWithBarrier(std::function<void()> barrier, std::vector<std::function<void()>>* functions)
		//{
		//	/*{
		//		std::unique_lock<std::mutex> lock(Queue_Mutex);
		//		JobQueue.push(barrier);
		//		barred_functions_[barrier] = functions;
		//	}
		//	condition.notify_one();**/
		//}

		void ThreadPool::terminate()
		{
			terminate_ = true;
			condition.notify_all();

			for (auto& t : Pool)
			{
				t.join();
			}
		}

		void ThreadPool::InfiniteLoop()
		{
			while (true)
			{
				std::function<void()> Job;
				{
					std::unique_lock<std::mutex> lock(Queue_Mutex);
					if (working_threads_ == 0)
					{
						condition_done.notify_one();
					}
					condition.wait(lock, [this] {return !JobQueue.empty() || terminate_; });

					if (terminate_)
					{
						--working_threads_;
						return;
					}

					Job = JobQueue.front();
					JobQueue.pop();
				}

				Job(); // function<void()> type
				
				--working_threads_;

				

				/*if(barred_functions_.find(Job) != barred_functions_.end())
				{
					for(std::function<void()> element : *barred_functions_[Job])
					{
						JobQueue.push(element);
					}

					delete barred_functions_[Job];
					barred_functions_.erase(Job);
				}*/
			}
		}

	}
}