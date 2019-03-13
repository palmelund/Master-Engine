#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

class Boss :
	public GameObject
{
public:
	Boss();
	~Boss();

	void start_up() override;
	void update() override;

	sf::Vector2f velocity;

private:
	int size_;
};

