#include "stdafx.h"
#include "IntDelta.h"
#include <limits>

IntDelta::IntDelta(IntWrapper * pointer) : original_value_(pointer), additions_(0), multiplications_(1), assign_(0), assign_priority_(std::numeric_limits<int>::min())
{

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
	if (assign_priority_ > 0)
	{
		original_value_->set_value(assign_);
		return;
	}
	original_value_->set_value(original_value_->get_value()*multiplications_ + additions_);

}
