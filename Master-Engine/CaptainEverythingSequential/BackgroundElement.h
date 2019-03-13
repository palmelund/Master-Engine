#pragma once
#include "../MasterEngineLibSequential/GameObject.h"
#include "M_Transform.h"

class BackgroundElement :
	public GameObject, M_Transform
{
public:
	BackgroundElement();
	~BackgroundElement();

	void update() override;
	void OnCollision(GameObject* collider) override;

private:
	int size_;
};

