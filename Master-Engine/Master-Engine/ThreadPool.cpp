#include "pch.h"
#include "ThreadPool.h"

#include <thread>
#include <vector>
#include <mutex>

std::queue<void(*)()> ThreadPool::JobQueue{};
std::vector<std::thread> ThreadPool::Pool{};

std::mutex ThreadPool::Queue_Mutex{};
std::condition_variable ThreadPool::condition{};

void ThreadPool::CreateThreadPool()
{
	int Num_Threads = std::thread::hardware_concurrency();

 	for (int ii = 0; ii < Num_Threads; ii++)
	{
		Pool.push_back(std::thread(InfiniteLoop));
	}
}

void ThreadPool::AddJob(void(*func)())
{
	{
		std::unique_lock<std::mutex> lock(Queue_Mutex);
		JobQueue.push(func);
	}
	condition.notify_one();
}

void ThreadPool::InfiniteLoop()
{
	while (true)
	{
		void(*Job)();
		{
			std::unique_lock<std::mutex> lock(Queue_Mutex);

			condition.wait(lock, [] {return !JobQueue.empty(); });
			Job = JobQueue.front();
			JobQueue.pop();
		}
		Job(); // function<void()> type
	}
}