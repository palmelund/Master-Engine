#pragma once
#include "../MasterEngineLibSequential/GameObject.h"
#include "M_Transform.h"

class PlayerBullet :
	public GameObject, M_Transform
{
public:
	PlayerBullet();
	~PlayerBullet();

	void update() override;
	void OnCollision(GameObject* collider) override;

private:
	int size_;
};

