#include "stdafx.h"
#include "IntWrapper.h"
#include "ThreadPool.h"
#include "IntDelta.h"


IntWrapper::IntWrapper()
{
	value_ = 0;
}


IntWrapper::~IntWrapper()
{
}

void IntWrapper::operator+=(const int & rhs)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	if (pointer_deltas->find(this) != pointer_deltas->end())
	{
		IntDelta* delta = static_cast<IntDelta*>(pointer_deltas->at(this));
		delta->addition(rhs);
	}
	else
	{
		IntDelta* new_delta = new IntDelta{ this };
		new_delta->addition(rhs);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}

void IntWrapper::operator*=(const int & rhs)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	if (pointer_deltas->find(this) != pointer_deltas->end())
	{
		IntDelta* delta = static_cast<IntDelta*>(pointer_deltas->at(this));
		delta->multiply(rhs);
	}
	else
	{
		IntDelta* new_delta = new IntDelta{ this };
		new_delta->multiply(rhs);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}

void IntWrapper::operator=(const int & rhs)
{
	assign(rhs, 1);
}

void IntWrapper::assign(const int & rhs, int priority)
{
	auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
	if (pointer_deltas->find(this) != pointer_deltas->end())
	{
		IntDelta* delta = static_cast<IntDelta*>(pointer_deltas->at(this));
		delta->assign(rhs, priority);
	}
	else
	{
		IntDelta* new_delta = new IntDelta{ this };
		new_delta->assign(rhs, priority);
		pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
	}
}

int IntWrapper::get_value()
{
	return value_;
}

void IntWrapper::set_value(int value)
{
	value_ = value;
}
