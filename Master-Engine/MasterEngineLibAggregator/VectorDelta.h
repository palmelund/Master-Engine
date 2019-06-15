#pragma once
#include "BaseDelta.h"
#include "BaseWrapper.h"
template <class T>
class VectorWrapper;

template <class T>
class VectorDelta final :
	public BaseDelta
{
public:
	explicit VectorDelta(BaseWrapper* pointer)
	{
		additions_ = {};
		removes_ = {};
		original_value_ = pointer;
	}

	void addition(T value)
	{
		additions_.emplace_back(value);
	}

	void remove(T value)
	{
		removes_.emplace_back(value);
	}

	void reduce(void* pointer) override
	{
		auto* target = static_cast<VectorDelta<T>*>(pointer);
		additions_.insert(additions_.end(), target->additions_.begin(), target->additions_.end());
		removes_.insert(removes_.end(), target->removes_.begin(), target->removes_.end());
	};
	void merge() override
	{
		auto* target = static_cast<VectorWrapper<T>*>(original_value_);
		target->adds_vector(additions_);
		target->removes_vector(removes_);
	}
private:
	std::vector<T> additions_;
	std::vector<T> removes_;
};



