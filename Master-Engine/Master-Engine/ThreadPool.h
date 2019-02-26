#pragma once
#include<vector>
#include<queue>
#include <mutex>

class ThreadPool
{
public:
	ThreadPool() = delete;
	~ThreadPool() = delete;

	static void CreateThreadPool();
	static void AddJob(void(*func)());
	template<typename CONTAINER>
	static void AddJob(const CONTAINER& container);
private:
	static void InfiniteLoop();

	static std::queue<void(*)()> JobQueue;
	static std::vector<std::thread> Pool;

	static std::mutex Queue_Mutex;
	static std::condition_variable condition;
};

template <typename CONTAINER>
void ThreadPool::AddJob(const CONTAINER& container)
{
	std::unique_lock<std::mutex> lock(Queue_Mutex);
	for (auto& func : container)
	{
		JobQueue.push(func);
	}
	condition.notify_all();		// TODO: ?
}

