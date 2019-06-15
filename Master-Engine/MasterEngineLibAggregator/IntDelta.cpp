#include "stdafx.h"
#include "IntDelta.h"
#include <limits>
#include "BaseWrapper.h"
#include "IntWrapper.h"

IntDelta::IntDelta(BaseWrapper * pointer) :  additions_(0), multiplications_(1), assign_(0), assign_priority_(std::numeric_limits<int>::min())
{
	original_value_ = pointer;
}

void IntDelta::assign(const int value, const int priority)
{
	if (assign_priority_ < priority)
	{
		assign_ = value;
		assign_priority_ = priority;
	}
}

void IntDelta::addition(const int value)
{
	additions_ += value;
}

void IntDelta::multiply(const int value)
{
	multiplications_ *= value;
}

void IntDelta::reduce(void* pointer)
{
	const auto target = static_cast<IntDelta*>(pointer);
	additions_ += target->additions_;
	multiplications_ *= target->multiplications_;
	assign(target->assign_, target->assign_priority_);
}

void IntDelta::merge()
{
	IntWrapper* original_pointer = static_cast<IntWrapper*>(original_value_);
	if (assign_priority_ > 0)
	{
		original_pointer->set_value(assign_);
		return;
	}
	original_pointer->set_value(original_pointer->get_value()*multiplications_ + additions_);

}
