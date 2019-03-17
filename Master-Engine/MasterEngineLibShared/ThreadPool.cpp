#include "stdafx.h"

#include <thread>
#include <vector>
#include <mutex>
#include "ThreadPool.h"
#include <map>

std::queue<void(*)()> ThreadPool::JobQueue{};
std::vector<std::thread> ThreadPool::Pool{};

std::mutex ThreadPool::Queue_Mutex{};
std::condition_variable ThreadPool::condition{};

std::map<void(*)(), std::vector<void(*)()>*> ThreadPool::barred_functions_{};

void ThreadPool::CreateThreadPool()
{
	const int Num_Threads = std::thread::hardware_concurrency();

 	for (int ii = 0; ii < Num_Threads; ii++)
	{
		Pool.emplace_back(InfiniteLoop);
	}
}

void ThreadPool::ClearThreadPool()
{
	std::queue<void(*)()> queue;
	std::swap(JobQueue, queue);

	for (auto i = 0; i < Pool.size(); i++)
	{
		JobQueue.push(nullptr);
	}

	condition.notify_all();

	for(auto& t : Pool)
	{
		t.join();
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

void ThreadPool::AddJobWithBarrier(void(*barrier)(), std::vector<void(*)()>* functions)
{
	{
		std::unique_lock<std::mutex> lock(Queue_Mutex);
		JobQueue.push(barrier);
		barred_functions_[barrier] = functions;
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

		if(Job == nullptr)
		{
			return;
		}

		Job(); // function<void()> type

		if(barred_functions_.find(Job) != barred_functions_.end())
		{
			for(auto* element : *barred_functions_[Job])
			{
				JobQueue.push(element);
			}

			delete barred_functions_[Job];
			barred_functions_.erase(Job);
		}
	}
}
