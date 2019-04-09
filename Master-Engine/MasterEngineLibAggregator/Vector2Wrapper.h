#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class Vector2Wrapper
{
public:
	Vector2Wrapper();
	~Vector2Wrapper();

	void operator+=(const sf::Vector2f& rhs);

	void operator=(const sf::Vector2f& rhs);

	void assign(const sf::Vector2f& rhs, int priority);

	const sf::Vector2f get_vector();

	void set_vector(sf::Vector2f);
private:
	sf::Vector2f value_;

};

