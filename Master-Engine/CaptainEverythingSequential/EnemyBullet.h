#pragma once
#include "../MasterEngineLibSequential/GameObject.h"
#include "M_Transform.h"

class EnemyBullet :
	public GameObject, M_Transform
{
public:
	EnemyBullet();
	~EnemyBullet();

	void start_up() override;
	void update() override;

private:
	int size_;
};

