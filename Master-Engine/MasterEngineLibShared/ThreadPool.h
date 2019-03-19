#pragma once
#include<vector>
#include<queue>
#include <mutex>
#include <map>

class ThreadPool
{
public:
	ThreadPool() = delete;
	~ThreadPool() = delete;

	static void CreateThreadPool();
	static void ClearThreadPool();
	static void AddJob(std::function<void()>);
	static void AddJobWithBarrier(std::function<void()>, std::vector<std::function<void()>>* functions);
	/*template<typename CONTAINER>
	static void AddJob(const CONTAINER& container);*/
	static std::condition_variable condition_done;
	static std::mutex Queue_Mutex;
	static std::queue<std::function<void()>> JobQueue;

private:
	static void InfiniteLoop();
	static std::condition_variable condition;
	static std::vector<std::thread> Pool;

	static std::map<std::function<void()>, std::vector<std::function<void()>>*> barred_functions_;
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
