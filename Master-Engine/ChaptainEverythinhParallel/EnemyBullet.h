#pragma once
#include "../MasterEngineLibParallel/GameObject.h"
#include <mutex>

class EnemyBullet :
	public GameObject
{
public:
	EnemyBullet();
	~EnemyBullet();

	void start_up() override;
	void update() override;

private:
	int size_;
};

