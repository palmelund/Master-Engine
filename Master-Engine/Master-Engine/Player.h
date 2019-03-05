#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	~Player();

	void update() override;
private:
	sf::Vector2f velocity;

	sf::Vector2f rotate_vector(sf::Vector2f);
};

