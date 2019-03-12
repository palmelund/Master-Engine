#pragma once
#include "G:\Git\Master-Engine\Master-Engine\MasterEngineLibSequential\GameObject.h"
class Enemy :
	public GameObject
{
public:
	Enemy(std::string);
	~Enemy();

	void start_up() override;
	void update() override;

	sf::Vector2f velocity;

private:
	int size_;
	float fire_rate_;
	float internal_timer;

};

