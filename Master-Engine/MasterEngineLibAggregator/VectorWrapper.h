#pragma once
#include <vector>
#include "BaseDelta.h"
#include "ThreadPool.h"
#include "VectorDelta.h"

template <class T>
class VectorWrapper
{
public:
	VectorWrapper()
	{
		value_ = {};
	}

	~VectorWrapper()
	{
	}

	void operator+=(const T& rhs)
	{
		auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
		if (pointer_deltas->find(this) != pointer_deltas->end())
		{
			VectorDelta<T>* delta = static_cast<VectorDelta<T>*>(pointer_deltas->at(this));
			delta->addition(rhs);
		}
		else
		{
			VectorDelta<T>* new_delta = new VectorDelta<T>{ this };
			new_delta->addition(rhs);
			pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
		}
	}

	void operator-=(const T& rhs)
	{
		auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
		if (pointer_deltas->find(this) != pointer_deltas->end())
		{
			VectorDelta<T>* delta = static_cast<VectorDelta<T>*>(pointer_deltas->at(this));
			delta->remove(rhs);
		}
		else
		{
			VectorDelta<T>* new_delta = new VectorDelta<T>{ this };
			new_delta->remove(rhs);
			pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
		}
	}

	void adds_vector(std::vector<T> value)
	{
		value_.insert(value_.end(), value.begin(), value.end());
	}

	void removes_vector(std::vector<T> value)
	{
		for(int i = 0; i < value.size(); i++)
		{
			const auto element = std::find(value_.begin(), value_.end(), value[i]);
			if (element != value_.end()) {
				value_.erase(element);
				delete value[i];
			}
		}
		
	}
	

	void clear()
	{
		value_.clear();
	}

	std::vector<T>& get_value()
	{
		return value_;
	}

private:
	std::vector<T> value_;
};
