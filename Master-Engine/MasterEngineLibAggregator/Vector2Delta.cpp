#include "stdafx.h"
#include "Vector2Delta.h"

Vector2Delta::Vector2Delta(Vector2Wrapper* org_pointer)
{
	orginal_value = org_pointer;
	assign_priority_ = 0;
	additions_ = {};
}

Vector2Delta::~Vector2Delta()
{
}

void Vector2Delta::addition(sf::Vector2f add)
{
	additions_.x += add.x;
	additions_.y += add.y;
}

void Vector2Delta::assign(sf::Vector2f value, int priority)
{
	if (assign_priority_ < priority)
	{
		assign_ = value;
		assign_priority_ = priority;
	}
}

void Vector2Delta::reduce(void* pointer)
{
	Vector2Delta* target = static_cast<Vector2Delta*>(pointer);
	addition(target->additions_);
	assign(target->assign_, target->assign_priority_);
}

void Vector2Delta::merge()
{
	if (assign_priority_ > 0)
	{
		orginal_value->set_vector(assign_);
		return;
	}
	orginal_value->set_vector(sf::Vector2f{ orginal_value->get_vector().x + additions_.x, orginal_value->get_vector().y + additions_.y });
}
