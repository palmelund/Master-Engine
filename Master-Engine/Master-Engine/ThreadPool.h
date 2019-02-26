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
private:
	static void InfiniteLoop();

	static std::queue<void(*)()> JobQueue;
	static std::vector<std::thread> Pool;

	static std::mutex Queue_Mutex;
	static std::condition_variable condition;
};

