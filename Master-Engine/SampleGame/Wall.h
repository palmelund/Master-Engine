#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

class Wall :
	public GameObject
{
public:
	Wall(const std::string&, sf::Vector2f, float);
	~Wall();
};

