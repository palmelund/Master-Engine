#pragma once
#include "../MasterEngineLibParallel/GameObject.h"

class GravityWell :
	public GameObject
{
public:
	GravityWell();
	~GravityWell();

	void OnCollision(GameObject* collider) override;
};

