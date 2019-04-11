#pragma once
#include "BaseDelta.h"
#include "VectorWrapper.h"

template <class T>
class VectorWrapper;

template <class T>
class VectorDelta :
	public BaseDelta
{
public:
	VectorDelta(VectorWrapper<T>* pointer)
	{
		orginal_value_ = pointer;
		additions_ = {};
		removes_ = {};
	}
	~VectorDelta()
	{
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
		VectorDelta<T>* target = static_cast<VectorDelta<T>*>(pointer);
		additions_.insert(additions_.end(), target->additions_.begin(), target->additions_.end());
		removes_.insert(removes_.end(), target->removes_.begin(), target->removes_.end());
	};
	void merge() override
	{
		VectorWrapper<T>* target = static_cast<VectorWrapper<T>*>(orginal_value_);
		target->adds_vector(additions_);
		target->removes_vector(removes_);
	}
private:
	VectorWrapper<T>* orginal_value_;

	std::vector<T> additions_;
	std::vector<T> removes_;
};



