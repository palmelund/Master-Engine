#pragma once
#include "../MasterEngineLibSequential/GameObject.h"

class GravityWell :
	public GameObject
{
public:
	GravityWell();
	~GravityWell();

	void OnCollision(GameObject* collider) override;
};

