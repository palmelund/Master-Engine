#pragma once
#include "G:\Git\Master-Engine\Master-Engine\MasterEngineLibSequential\GameObject.h"
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

