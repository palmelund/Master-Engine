#pragma once

#include <SFML/System/Vector2.hpp>

class GenericHelper
{
public:
	static void init();
	static sf::Vector2f get_position(int index);
	static sf::Vector2f get_velocity();
};

