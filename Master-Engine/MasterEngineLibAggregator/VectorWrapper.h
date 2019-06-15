#pragma once
#include <vector>
#include "BaseDelta.h"
#include "BaseWrapper.h"
#include "ThreadPool.h"
#include "VectorDelta.h"

template <class T>
class VectorWrapper final : public BaseWrapper
{
public:
	VectorWrapper()
	{
		value_ = {};
	}

	void operator+=(const T& rhs)
	{
		auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
		auto pointer = pointer_deltas->find(this);
		if (pointer != pointer_deltas->end())
		{
			auto delta = static_cast<VectorDelta<T>*>((*pointer).second);
			delta->addition(rhs);
		}
		else
		{
			auto* new_delta = new VectorDelta<T>{ this };
			new_delta->addition(rhs);
			pointer_deltas->insert(std::pair<void*, BaseDelta*>(this, new_delta));
		}
	}

	void operator-=(const T& rhs)
	{
		auto* pointer_deltas = &MasterEngine::LibAggregator::ThreadPool::deltas[std::this_thread::get_id()];
		auto pointer = pointer_deltas->find(this);
		if (pointer != pointer_deltas->end())
		{
			auto delta = static_cast<VectorDelta<T>*>((*pointer).second);
			delta->remove(rhs);
		}
		else
		{
			auto* new_delta = new VectorDelta<T>{ this };
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
		for(auto i = 0; i < value.size(); i++)
		{
			const auto element = std::find(value_.begin(), value_.end(), value[i]);
			if (element != value_.end()) {
				value_.erase(element);

			}
		}

	}

	void reset() override {}

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
