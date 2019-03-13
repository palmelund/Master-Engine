#pragma once
#include <SFML/System/Vector2.hpp>

class M_Transform
{
public:
	M_Transform();
	~M_Transform();

	void add_velocity(sf::Vector2f);
	void set_velocity(sf::Vector2f);

	sf::Vector2f get_velocity();

private:
	sf::Vector2f velocity_;
};

