#pragma once
#include "BaseWrapper.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

class Vector2Wrapper : public BaseWrapper
{
public:
	Vector2Wrapper(void*);
	~Vector2Wrapper();

	void operator+=(const sf::Vector2f& rhs);

	void reduce(void*) override;
	void merge() override;
private:
	std::vector<sf::Vector2f> additions;
	sf::Vector2f value;
};

