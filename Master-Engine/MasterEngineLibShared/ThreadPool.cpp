#include "stdafx.h"

#include <thread>
#include <vector>
#include <mutex>
#include "ThreadPool.h"
#include <map>

std::queue<std::function<void()>> ThreadPool::JobQueue{};
std::vector<std::thread> ThreadPool::Pool{};

std::mutex ThreadPool::Queue_Mutex{};
std::condition_variable ThreadPool::condition{};
std::condition_variable ThreadPool::condition_done{};

std::map<std::function<void()>, std::vector<std::function<void()>>*> ThreadPool::barred_functions_{};

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
	std::queue<std::function<void()>> queue;
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

void ThreadPool::AddJob(std::function<void()> func)
{
	{
		std::unique_lock<std::mutex> lock(Queue_Mutex);
		JobQueue.push(func);
	}
	condition.notify_one();
}

void ThreadPool::AddJobWithBarrier(std::function<void()> barrier, std::vector<std::function<void()>>* functions)
{
	/*{
		std::unique_lock<std::mutex> lock(Queue_Mutex);
		JobQueue.push(barrier);
		barred_functions_[barrier] = functions;
	}
	condition.notify_one();*/
}

void ThreadPool::InfiniteLoop()
{
	while (true)
	{
		std::function<void()> Job;
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
		condition_done.notify_one();
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
