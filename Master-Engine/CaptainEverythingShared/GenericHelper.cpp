#include "pch.h"
#include "GenericHelper.h"

#include "halton.h"

void GenericHelper::init()
{
	srand(42);
}

sf::Vector2f GenericHelper::get_position(int index)
{
	const auto halton_ptr = halton(index, 2);
	sf::Vector2f pos;
	pos.x = halton_ptr[0];
	pos.y = halton_ptr[1];

	delete halton_ptr;

	return  pos;


}

sf::Vector2f GenericHelper::get_velocity()
{
	auto rand_val = rand();
	return sf::Vector2f{ static_cast<float>(std::cos(rand_val)) * 100, static_cast<float>(std::sin(rand_val)) * 100 };
}
