#pragma once
#include<vector>
#include<queue>
#include <mutex>
#include <map>
#include <atomic>

namespace MasterEngine {
	namespace LibShared {

		class ThreadPool
		{
		public:
			ThreadPool();
			~ThreadPool();

			void CreateThreadPool();
			void ClearThreadPool();
			void AddJob(std::function<void()>);
			void AddJobWithBarrier(std::function<void()>, std::vector<std::function<void()>>* functions);
			/*template<typename CONTAINER>
			static void AddJob(const CONTAINER& container);*/
			std::condition_variable condition_done;
			std::mutex Queue_Mutex;
			std::queue<std::function<void()>> JobQueue;

			int thread_count() const noexcept;
			void terminate();

			std::atomic<int> working_threads_;
		private:
			void InfiniteLoop();
			std::condition_variable condition;
			std::vector<std::thread> Pool;

			std::map<std::function<void()>, std::vector<std::function<void()>>*> barred_functions_;
			
			std::atomic<int> thread_count_;

			bool terminate_;

			std::mutex inc_dec_lock_;
		};

		/*template <typename CONTAINER>
		void ThreadPool::AddJob(const CONTAINER& container)
		{
			std::unique_lock<std::mutex> lock(Queue_Mutex);
			for (auto& func : container)
			{
				JobQueue.push(func);
			}
			condition.notify_all();		// TODO: ?
		}*/

	}
}
