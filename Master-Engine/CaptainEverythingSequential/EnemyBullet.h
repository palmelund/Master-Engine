#pragma once
#include "G:\Git\Master-Engine\Master-Engine\MasterEngineLibSequential\GameObject.h"
class EnemyBullet :
	public GameObject
{
public:
	EnemyBullet();
	~EnemyBullet();

	void start_up() override;
	void update() override;

	sf::Vector2f velocity;

private:
	int size_;
};

