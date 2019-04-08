#include "stdafx.h"
#include "Vector2Wrapper.h"
#include <vector>
#include "thread"


Vector2Wrapper::Vector2Wrapper(void * pointer) : BaseWrapper(pointer)
{
	additions = {};
	value = {};
}

Vector2Wrapper::~Vector2Wrapper()
{
}

void Vector2Wrapper::operator+=(const sf::Vector2f& rhs) 
{
	additions.emplace_back(rhs);
}

void Vector2Wrapper::reduce(void* reduce_target)
{
	auto* reduces = static_cast<Vector2Wrapper*>(reduce_target);
	additions.insert(additions.end(), reduces->additions.begin(), reduces->additions.end());
}

void Vector2Wrapper::merge()
{
	for (auto vector2 : additions)
	{
		value = sf::Vector2f{ value.x + vector2.x, value.y + vector2.y };
	}
	additions.clear();
}



