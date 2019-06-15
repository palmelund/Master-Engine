#include "stdafx.h"
#include "Vector2Delta.h"
#include "BaseWrapper.h"
#include "Vector2Wrapper.h"

Vector2Delta::Vector2Delta(BaseWrapper* org_pointer) : assign_priority_(0)
{
	additions_ = {};
	original_value_ = org_pointer;
	
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
	Vector2Wrapper* orginal_pointer = static_cast<Vector2Wrapper*>(original_value_);
	if (assign_priority_ > 0)
	{
		orginal_pointer->set_vector(assign_);
		return;
	}

	orginal_pointer->set_vector(sf::Vector2f{ orginal_pointer->get_vector().x + additions_.x, orginal_pointer->get_vector().y + additions_.y });
}
