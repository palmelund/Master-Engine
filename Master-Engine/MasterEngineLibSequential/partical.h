#pragma once
#include "GameObject.h"
class partical :
	public GameObject
{
public:
	partical(const std::string&, sf::Vector2f, sf::Vector2f);
	~partical();

	void update() override;
private:
	sf::Vector2f velocity_;
	float size_;
};

