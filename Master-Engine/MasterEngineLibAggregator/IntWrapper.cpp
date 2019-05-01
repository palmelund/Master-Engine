#include "stdafx.h"
#include "IntWrapper.h"
#include "ThreadPool.h"
#include "IntDelta.h"


IntWrapper::IntWrapper()
{
	value_ = 0;
}

void IntWrapper::operator+=(const int & rhs)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	if (pointer_deltas->find(this) != pointer_deltas->end())
	{
		auto delta = static_cast<IntDelta*>(pointer_deltas->at(this));
		delta->addition(rhs);
	}
	else
	{
		auto new_delta = new IntDelta{ this };
		new_delta->addition(rhs);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}

void IntWrapper::operator*=(const int & rhs)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	if (pointer_deltas->find(this) != pointer_deltas->end())
	{
		auto delta = static_cast<IntDelta*>(pointer_deltas->at(this));
		delta->multiply(rhs);
	}
	else
	{
		auto new_delta = new IntDelta{ this };
		new_delta->multiply(rhs);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}

void IntWrapper::operator=(const int & rhs)
{
	assign(rhs, 1);
}

void IntWrapper::assign(const int & rhs, const int priority)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	auto pointer = pointer_deltas->find(this);
	if (pointer != pointer_deltas->end())
	{
		auto delta = static_cast<IntDelta*>((*pointer).second);
		delta->assign(rhs, priority);
	}
	else
	{
		auto new_delta = new IntDelta{ this };
		new_delta->assign(rhs, priority);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}

int IntWrapper::get_value() const
{
	return value_;
}

void IntWrapper::set_value(const int value)
{
	value_ = value;
}
