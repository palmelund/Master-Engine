#pragma once
#include <SFML/System/Vector2.hpp>

class Vector2Wrapper
{
public:
	Vector2Wrapper();

	void operator+=(const sf::Vector2f& rhs);

	void operator=(const sf::Vector2f& rhs);

	void assign(const sf::Vector2f& rhs, int priority);

	sf::Vector2f get_vector() const;

	void set_vector(sf::Vector2f);
private:
	sf::Vector2f value_;

};

