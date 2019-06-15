#include "stdafx.h"
#include "Vector2Wrapper.h"
#include <vector>
#include "thread"
#include "ThreadPool.h"
#include "Vector2Delta.h"
#include "ThreadPool.h"

Vector2Wrapper::Vector2Wrapper()
{
	value_ = {};
	for (auto id : MasterEngine::LibAggregator::ThreadPool::threads_ids) {
		local_delta_list[id] = nullptr;
	}
}

void Vector2Wrapper::operator+=(const sf::Vector2f& rhs)
{
	
	auto pointer = local_delta_list.find(std::this_thread::get_id());
	if (pointer != local_delta_list.end() && (*pointer).second != nullptr)
	{
		auto delta = static_cast<Vector2Delta*>((*pointer).second);
		delta->addition(rhs);
	}
	else
	{
		auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
		auto new_delta = new Vector2Delta{ this };
		new_delta->addition(rhs);
		
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
		local_delta_list[std::this_thread::get_id()] = new_delta;
	}
}

void Vector2Wrapper::operator=(const sf::Vector2f& rhs)
{
	assign(rhs, 1);
}

void Vector2Wrapper::assign(const sf::Vector2f& rhs, const int priority)
{
	
	auto pointer = local_delta_list.find(std::this_thread::get_id());
	if (pointer != local_delta_list.end() && (*pointer).second != nullptr)
	{
		auto delta = static_cast<Vector2Delta*>((*pointer).second);
		delta->assign(rhs, priority);
	}
	else
	{
		auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
		auto new_delta = new Vector2Delta{ this };
		new_delta->assign(rhs, priority);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
		local_delta_list[std::this_thread::get_id()] = new_delta;
	}
}

void Vector2Wrapper::reset()
{
	for (auto id : MasterEngine::LibAggregator::ThreadPool::threads_ids) {
		local_delta_list[id] = nullptr;
	}
}


sf::Vector2f Vector2Wrapper::get_vector() const
{
	return value_;
}

void Vector2Wrapper::set_vector(const sf::Vector2f val)
{
	value_ = val;
}





