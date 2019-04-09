#include "stdafx.h"
#include "Vector2Wrapper.h"
#include <vector>
#include "thread"
#include "ThreadPool.h"
#include "Vector2Delta.h"


Vector2Wrapper::Vector2Wrapper() 
{
	value_ = {};
}

Vector2Wrapper::~Vector2Wrapper()
{
}

void Vector2Wrapper::operator+=(const sf::Vector2f& rhs)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	if (pointer_deltas->find(this) != pointer_deltas->end())
	{
		Vector2Delta* delta = static_cast<Vector2Delta*>(pointer_deltas->at(this));
		delta->addition(rhs);
	}
	else
	{
		Vector2Delta* new_delta = new Vector2Delta{ this };
		new_delta->addition(rhs);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}

void Vector2Wrapper::operator=(const sf::Vector2f& rhs)
{
	assign(rhs, 1);
}

void Vector2Wrapper::assign(const sf::Vector2f& rhs, int priority)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	if (pointer_deltas->find(this) != pointer_deltas->end())
	{
		Vector2Delta* delta = static_cast<Vector2Delta*>(pointer_deltas->at(this));
		delta->assign(rhs, priority);
	}
	else
	{
		Vector2Delta* new_delta = new Vector2Delta{ this };
		new_delta->assign(rhs, priority);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}


const sf::Vector2f Vector2Wrapper::get_vector()
{
	return value_;
}

void Vector2Wrapper::set_vector(sf::Vector2f val)
{
	value_ = val;
}





