#include "stdafx.h"
#include "IntDelta.h"

IntDelta::IntDelta(IntWrapper * pointer) 
{
	orginal_value_ = pointer;
	multiplys_ = 1;
}

IntDelta::~IntDelta()
{
}

void IntDelta::assign(int value, int priority)
{
	if (assing_priority_ < priority)
	{
		assign_ = value;
		assing_priority_ = priority;
	}
}

void IntDelta::addition(int value)
{
	additions_ += value;
}

void IntDelta::multiply(int value)
{
	multiplys_ *= value;
}

void IntDelta::reduce(void* pointer)
{
	IntDelta* target = static_cast<IntDelta*>(pointer);
	additions_ += target->additions_;
	multiplys_ *= target->multiplys_;
	assign(target->assign_, target->assing_priority_);
}

void IntDelta::merge()
{
	if (assing_priority_ > 0)
	{
		orginal_value_->set_value(assign_);
		return;
	}
	orginal_value_->set_value(orginal_value_->get_value()*multiplys_ + additions_);

}
