#include "stdafx.h"
#include "Vector2Delta.h"

Vector2Delta::Vector2Delta(Vector2Wrapper* org_pointer) : original_value_(org_pointer), assign_priority_(0)
{
	additions_ = {};
}

void Vector2Delta::addition(const sf::Vector2f add)
{
	additions_.x += add.x;
	additions_.y += add.y;
}

void Vector2Delta::assign(const sf::Vector2f value, const int priority)
{
	if (assign_priority_ < priority)
	{
		assign_ = value;
		assign_priority_ = priority;
	}
}

void Vector2Delta::reduce(void* pointer)
{
	const auto target = static_cast<Vector2Delta*>(pointer);
	addition(target->additions_);
	assign(target->assign_, target->assign_priority_);
}

void Vector2Delta::merge()
{
	if (assign_priority_ > 0)
	{
		original_value_->set_vector(assign_);
		return;
	}
	original_value_->set_vector(sf::Vector2f{ original_value_->get_vector().x + additions_.x, original_value_->get_vector().y + additions_.y });
}
